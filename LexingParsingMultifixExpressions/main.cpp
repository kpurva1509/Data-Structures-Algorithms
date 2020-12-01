#include "headers.hpp"

struct Token{
    enum Type {plus, minus, divide, multiply, leftparen, rightparen, integer} type;
    std::string text;
    Token(){}
    Token(Type type, std::string text): type(type), text(text) {}
    Token(const Token& rhs){
        type = rhs.type;
        text = rhs.text;
    }
    Token& operator=(const Token& rhs) {
        type = rhs.type;
        text = rhs.text;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& out, const Token& token);
};

std::ostream &operator<<(std::ostream &out, const Token &token) {
    out << "The token is of the type " << token.type << " and has the expression " << token.text;
    return out;
}

std::vector<Token> lexInfixExpression(const std::string& infixExpression) {
    std::vector<Token> lexedExpression;
    lexedExpression.reserve(infixExpression.length()); 
    int i=0;
    for(;infixExpression[i] != '\0'; i++) {
        switch (infixExpression[i]) {
            case '+':
                lexedExpression.push_back(Token(Token::plus, "+"));
                break;
            case '-':
                lexedExpression.push_back(Token(Token::minus, "-"));
                break;
            case '*':
                lexedExpression.push_back(Token(Token::multiply, "*"));
                break;
            case '/':
                lexedExpression.push_back(Token(Token::divide, "/"));
                break;
            case '(':
                lexedExpression.push_back(Token(Token::leftparen, "("));
                break;
            case ')':
                lexedExpression.push_back(Token(Token::rightparen, ")"));
                break;
            default: 
                std::ostringstream buffer;
                buffer << infixExpression[i];
                for(int j=i+1; j<infixExpression.length(); j++) {
                    if(std::isdigit(infixExpression[j])) {
                        buffer << infixExpression[j];
                        i++;
                    } else {
                        lexedExpression.push_back(Token(Token::integer, buffer.str()));
                    }
                }
        }
    }
    return lexedExpression;
}

struct Element{
    virtual int eval() const = 0;
};

struct Operand : Element {
    int value;
    Operand(const int& value):value(value){}
    virtual int eval() const override {
        return value;
    }
};

struct Operator : Element {

    enum Type { plus, minus, multiply, divide} type;
    /* Pointer to parent can be derefered to 
     * child and recursively called */
    std::shared_ptr<Element> left, right;

    virtual int eval() const override {
        auto lhs = left->eval();
        auto rhs = right->eval();
        switch(type) {
            case plus: return lhs + rhs;
            case minus: return lhs - rhs;
            case multiply: return lhs*rhs;
            case divide: return lhs/rhs;
        }
    }
};

std::shared_ptr<Element> parse(const std::vector<Token>& lexedInfixExpression) {
    
    auto result = std::make_shared<Operator>();
    bool have_lhs = false;

    for(int i=0; i<lexedInfixExpression.size(); i++) {
        auto& token = lexedInfixExpression[i];
        switch(token.type){
            case Token::plus:
                result->type = Operator::plus;
                break;
            case Token::minus:
                result->type = Operator::minus;
                break;
            case Token::multiply:
                result->type = Operator::multiply;
                break;
            case Token::divide:
                result->type = Operator::divide;
                break;
            case Token::integer:
                {
                    int value = std::stoi(token.text);
                    auto integer = std::make_shared<Operand>(value);
                    if(!have_lhs){
                        result->left = integer;
                        have_lhs = true;
                    } else result->right = integer;
                }
                break;
            case Token::leftparen:
                {
                    int j=i;
                    for(; j<lexedInfixExpression.size(); j++) {
                        if(lexedInfixExpression[j].type == Token::rightparen) break;
                    }
                    std::vector<Token> subexpression(&lexedInfixExpression[i+1], &lexedInfixExpression[j]);
                    auto subelement = parse(subexpression);
                    if(!have_lhs){
                        result->left = subelement;
                        have_lhs = true;
                    } else result->right = subelement;
                    i = j;
                }
                break;
        }
    }
    return result;
}


inline bool isOperator(const char& input) {
    if(input == '+' || input == '-' || input == '*' || input == '/' || input == '(' || input == ')') return true;
    return false;
}

bool precedence(const char& operator1, const char& operator2) {

    if(operator1 == '(' && operator2 == '(') return false;
    if(operator2 == ')') return true;

    if(operator1 == '*' || operator1 == '/') {
        if (operator2 == '*' || operator2 == '/' || operator2 == '+' || operator2 == '-'){
            return true;
        } else return false;
    }

    if (operator1 == '+' || operator1 == '-'){
        if (operator1 == '+' || operator1 == '-') {
            return true;
        } else return false;
    }
    return false;
}

Token getOperatorType(const char& binaryOperator) {
    switch(binaryOperator){
        case '+':return Token(Token::plus, "+");
        case '-':return Token(Token::minus, "-");
        case '*':return Token(Token::plus, "*");
        case '/':return Token(Token::minus, "/");
        case '(':return Token(Token::minus, "/");
        case ')':return Token(Token::minus, "/");
    }
    return Token();
}

std::vector<Token> lexToPostfixExpression(const std::string& infixExpression) {

    std::vector<Token> postfixExpression;
    postfixExpression.reserve(infixExpression.length());
    std::stack<char> operatorStack;

    int i=0;
    for(;infixExpression[i]!='\0';i++){
        if (std::isdigit(infixExpression[i])) {
            std::ostringstream buffer;
            buffer << infixExpression[i];
            for(int j = i+1; j < infixExpression.length(); j++) {
                if(std::isdigit(infixExpression[j])) {
                    buffer << infixExpression[j];
                    i++;
                } else {
                    postfixExpression.push_back(Token(Token::integer, buffer.str()));
                }
            }
        } else if (isOperator(infixExpression[i])) {
            while(!operatorStack.empty() && precedence(operatorStack.top(), infixExpression[i])) {
                char topOperator = operatorStack.top();
                operatorStack.pop();
                /* reference to type 'const std::__1::__vector_base<Token, std::__1::allocator<Token> >::value_type' (aka 'const Token') could not bind to an lvalue of type 'Token (const char &)'*/
                postfixExpression.push_back(getOperatorType(topOperator));
            }
            if(infixExpression[i] == ')') {
                operatorStack.pop();
            } else{
                operatorStack.push(infixExpression[i]);
            }
        }
    }

    while(!operatorStack.empty()) {
        char topOperator = operatorStack.top();
        operatorStack.pop();
        postfixExpression.push_back(getOperatorType(topOperator));
    }
    postfixExpression.shrink_to_fit();
    return postfixExpression;
}
/*
std::shared_ptr<Element> parsePostfix(const std::vector<Token>& postfixExpression) {

    auto result = std::make_shared<Operator>();
    bool have_lhs = false;
    // static std::stack<char> operatorStack;

    for(int i=0; i < postfixExpression.size(); i++) {
        auto& token = postfixExpression[i];
        if (token.type == Token::integer){
                int value = std::stoi(token.text);
                auto integer = std::make_shared<Operand>(value);
                if (!have_lhs)
                {
                    result->left = integer;
                    have_lhs = true;
                }
                else result->right = integer;
        } else if (token.type == Token::plus || token.type == Token::minus || token.type == Token::multiply || token.type == Token::divide) {
           
        }
    }

    return result;
}
*/

int eval(const int& operand1, const int& operand2, Token token) {

    switch (token.type)
    {
    case Token::plus:
        return operand1 + operand2;
        break;
    case Token::minus:
        return operand1 - operand2;
        break;
    case Token::multiply:
        return operand1 * operand2;
        break;
    case Token::divide:
        return operand1 / operand2;
        break;
    default:
        break;
    }
    return -1;
}

double parsePostfix(const std::vector<Token>& postfixExpression) {

    double result = 0.0;
    std::stack<int> operandStack;

    for(int i=0; i<postfixExpression.size(); i++) {
        auto& token = postfixExpression[i];
        if(token.type == Token::integer){
            operandStack.push(std::stoi(token.text));
        }else if (token.type == Token::plus || token.type == Token::minus || token.type == Token::multiply || token.type == Token::divide) {
            auto operand2 = operandStack.top();
            operandStack.pop();
            auto operand1 = operandStack.top();
            operandStack.pop();
            int result = eval(operand1, operand2, token);
            operandStack.push(result);
        }
    }
    result = operandStack.top();
    operandStack.pop();
    return result;
}

void reverseInfixInput(std::string& infixExpression) {

    const int lower_bound = 0;
    int upper_bound = infixExpression.length()-1;
    const std::string::iterator iter = infixExpression.end() - 1;

    while(upper_bound > 0) {
        int i = lower_bound;
        if(std::isdigit(infixExpression[i])) {
            std::ostringstream buffer;
            buffer << infixExpression[i];
            for(int k=i+1; k < infixExpression.length(); k++) {
                if(std::isdigit(infixExpression[k])){
                    buffer << infixExpression[k];
                    i++;
                }
            }
            /* convert buffer into string, rotate it by(i+1) 
             * to the left, and append buffer to end of the string
             */
            std::string integer_input = buffer.str();
            std::rotate(infixExpression.begin(), infixExpression.begin() + (i + 1), iter);
        } else if(isOperator(infixExpression[i])) {
            if(infixExpression[i] == '(' || infixExpression[i] == ')') {
                /*??????????????????????????????????????????????????*/
            } else {
                std::rotate(infixExpression.begin(), infixExpression.begin() +(i+1), iter);
            }
        }

        upper_bound = upper_bound - (i+1);
    }
}

void interchangeBrackets(std::string& infixExpression) {
    std::for_each(infixExpression.begin(), infixExpression.end(),
        [](char& c) mutable {
            if(c == '(') c = ')';
            else if(c == ')') c = '(';
        });
}

std::vector<Token> lexToPrefixExpression(std::string& infixExpression) {

    std::vector<Token> prefixExpression;
    prefixExpression.reserve(infixExpression.length());
    std::stack<char> operatorStack;

    std::reverse(infixExpression.begin(), infixExpression.end());
    interchangeBrackets(infixExpression);
    int i=0;
    for(;i<infixExpression.length(); i++) {
        if(std::isdigit(infixExpression[i])) {
            std::ostringstream buffer;
            buffer << infixExpression[i];
            for(int j=i+1; i<infixExpression.length(); j++) {
                if(std::isdigit(infixExpression[j])) {
                    buffer << infixExpression[j];
                }
            }
            std::string integer = buffer.str();
            std::reverse(integer.begin(), integer.end());
            prefixExpression.push_back(Token(Token::integer, integer));
        }
        else if(isOperator(infixExpression[i])) {
            while(!operatorStack.empty()) {
                if (precedence(operatorStack.top(), infixExpression[i])) {
                    char topOperator = operatorStack.top();
                    operatorStack.pop();
                    prefixExpression.push_back(getOperatorType(infixExpression[i]));
                } else {
                    operatorStack.push(infixExpression[i]);
                }
            }
            operatorStack.push(infixExpression[i]);
        }
    }

    while(!operatorStack.empty()){
        char topOperator = operatorStack.top();
        operatorStack.pop();
        prefixExpression.push_back(getOperatorType(topOperator));
    }

    std::reverse(prefixExpression.begin(), prefixExpression.end());
    prefixExpression.shrink_to_fit();
    return prefixExpression;
}

int main() {


    return 0;
}