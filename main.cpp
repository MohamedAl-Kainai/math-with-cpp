#include <iostream>
#include <numeric>

using namespace std;

const string NUMBERS = "0123456789";
const string SMALL_NUMBERS = "₀₁₂₃₄₅₆₇₈₉";

const char PLUS     = '+';
const char MINUS    = '-';
const char MULTIPLY = '*';
const char DIVIDE   = '/';

const char RULER  = '-';
const int padding = 1;


void printArray(string *data, int size){
    cout << "[";
    for(int i=0; i < size; i++)
    {
        if (size == i+1)
        {
            cout << data[i];
        } else {
            cout << data[i] << ", ";
        }
    }
    cout << "]";
}

template <typename T>
void print(T const & value)
{
    cout << value << endl;
}

class Lexer{
    public:
        string basicTokens[100];
        string equalSizeTokens[100];
        int tokensLen = 0;

        Lexer(string userText){
            int tokensIndex = 0;
            for (int i=0; i < userText.length(); i++){
                if (isOp(userText[i])){
                    tokensLen += 2;
                    tokensIndex++;
                    basicTokens[tokensIndex] = userText[i];
                    tokensIndex++;
                } else {
                    if (NUMBERS.find(userText[i]) != std::string::npos){
                        basicTokens[tokensIndex] += userText[i];
                    }
                }
            }
            tokensLen++;

            string token="";
                int i2 = 0, _ruler = rulerLength();
                for(int i=0; i < tokensLen; i += 2){
                    for(int j=0; j < (_ruler-basicTokens[i].length()); j++){
                        token += " ";
                    }
                    token += basicTokens[i];
                    equalSizeTokens[i] = token;
                    token = "";
                }
        }

        bool isOp(char chr){
            return chr == PLUS || chr == MINUS || chr == MULTIPLY || chr == DIVIDE;
        }

        int result(){
            int output = stoi(basicTokens[0]);
            char chr;
            for(int i=0; i < tokensLen; i++){
                for(int j=0; j < basicTokens[i].length(); j++){
                    chr = basicTokens[i][j];
                    switch(chr){
                        case PLUS:
                            output += stoi(basicTokens[i+1]);
                            break;
                        case MINUS:
                            output -= stoi(basicTokens[i+1]);
                            break;
                        case MULTIPLY:
                            output *= stoi(basicTokens[i+1]);
                            break;
                        case DIVIDE:
                            output /= stoi(basicTokens[i+1]);
                            break;
                        default:
                            continue;
                    }
                }
            }
            return output;
        }

        int rulerLength(){
            return to_string(result()).length();
        }

        void drawRuler(){
            drawPadding();
            for(int i=0; i < rulerLength(); i++){
                cout << RULER;
            }
            cout << endl;
        }

        void drawPadding(){
            for(int i=0; i < padding; i++){
                cout << " ";
            }
        }
};

class Plus: public Lexer {
    public:
        Plus(string x): Lexer(x){ }

        void drawResult(){
            // numbers
            for(int i=0; i < tokensLen; i += 2){
                if (basicTokens[i-1] == ""){
                    drawPadding();
                }
                cout << basicTokens[i-1] << equalSizeTokens[i] << endl;
            }

            // stored numbers
            string storedNumbersLine = " ";
            int maxLength = rulerLength();
            for(int i=0; i < maxLength; i++){
                for(int j=0; j < tokensLen; j += 2){
                    cout << "normal: " << equalSizeTokens[j][i] << endl;
                }
            }

            // ruler
            drawRuler();

            // result
            drawPadding();
            cout << result();
        }
};

void intro(){
    cout << "Select your operator." << endl;
    cout << " 1. Plus\n 2. Minus\n 3. Multiply\n 4. Divide\n 5. to exit\n" << endl;
}


int main(){
    Plus plusObj("100+200");
    plusObj.drawResult();

    return 0;
}









//    string test[] = {"name122", "name2", "name3"};
//    cout << sizeof(test)/sizeof(test[0]) << endl;
//
//    string test1 = "name122";
//    cout << test1.length() << endl;


//    int selectNumber, num1, num2;
//    system("clear");
//    intro();
//    while(true)
//    {
//        cout << ":";
//        cin >> selectNumber;
//        switch (selectNumber)
//        {
//            case 1:
//                plusObj("100+100");
//                break;
//            case 2:
//                break;
//            case 3:
//                break;
//            case 4:
//                break;
//            case 5:
//                goto loop1;
//                break;
//            default:
//                cout << "no found!" << endl;
//                goto loop1;
//                break;
//        }
//    } loop1: ;