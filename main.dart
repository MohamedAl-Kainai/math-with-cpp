import 'dart:io';

const String NUMBERS = "0123456789";
const String SMALL_NUMBERS = "₀₁₂₃₄₅₆₇₈₉";

const String PLUS = '+';
const String MINUS = '-';
const String MULTIPLY = '*';
const String DIVIDE = '/';

const String RULER = '-';
const int padding = 1;

class Lexer {
  List<String> basicTokens = [];
  List<String> equalSizeTokens = [];
  int tokensLen = 0;
  String userText;

  Lexer(this.userText) {
    int tokensIndex = 0;
    for (int i = 0; i < userText.length; i++) {
      if (isOp(userText[i])) {
        tokensLen += 2;
        tokensIndex++;
        basicTokens.insert(tokensIndex, userText[i]);
        tokensIndex++;
      } else {
        try{
          basicTokens.insert(tokensIndex, basicTokens[tokensIndex]+userText[i]);
        } catch(RangeError){
          basicTokens.insert(tokensIndex, userText[i]);
        }
      }
    }
    tokensLen++;

    String token = "";
    int i2 = 0, _ruler = rulerLength();
    for (int i = 0; i < tokensLen; i += 2) {
      for (int j = 0; j < (_ruler - basicTokens[i].length); j++) {
        token += " ";
      }
      token += basicTokens[i];
      equalSizeTokens.add(token);
      token = "";
    }
  }

  bool isOp(String chr) {
    return chr == PLUS || chr == MINUS || chr == MULTIPLY || chr == DIVIDE;
  }

  num result() {
    num output = num.parse(basicTokens[0]);
    String chr;
    for (int i = 0; i < tokensLen; i++) {
      for (int j = 0; j < basicTokens[i].length; j++) {
        chr = basicTokens[i][j];
        switch (chr) {
          case PLUS:
            output += num.parse(basicTokens[i + 1]);
            break;
          case MINUS:
            output -= num.parse(basicTokens[i + 1]);
            break;
          case MULTIPLY:
            output *= num.parse(basicTokens[i + 1]);
            break;
          case DIVIDE:
            output /= num.parse(basicTokens[i + 1]);
            break;
          default:
            continue;
        }
      }
    }
    return output;
  }

  int rulerLength() {
    return result().toString().length;
  }

  void drawRuler() {
    drawPadding();
    print(RULER * rulerLength());
  }

  void drawPadding() {
    stdout.write(" " * padding);
  }
}

void main() {
  Lexer lexer = Lexer("100+100");
  print(lexer.result());
}
