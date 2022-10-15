/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
using namespace std;

/* This function is intended to return a string which
 * contains only the letter characters from the original
 * (all non-letter characters are removed)
 *
 * WARNING: The provided code is buggy!
 *
 * Use unit tests to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */
string removeNonLetters(string s) {
    string result = charToString(s[0]);
     int tol=0;
    for(int j=0;j<s.length();j++){

       if(isalpha(s[j]))
            tol++;}
    if(tol==0)
        return result="";

    for (int i = 1; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}
STUDENT_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
    s="    ";
    result=removeNonLetters(s);
    EXPECT_EQUAL(result,"");
    s="''1''1'";
    result=removeNonLetters(s);
    EXPECT_EQUAL(result,"");
}


//2、步骤二，根据下表编码每一个字母
string changeTostring(string s){
    string result;                   //考虑过switch 但是判断情况过多，会搞成case(AEI......)能力hold不住
    string zero="AEIOUHWY";
    string first="BFPV";
    string second="CGJKQSXZ";
    string third="DT";
    string forth="L";
    string fifth="MN";
    string sixth="R";
    string s2= removeNonLetters(s);
    for(int i=0;i<s2.length();i++)
    { char ch=toUpperCase(s2[i]);
        if(zero.find(ch)!=string::npos)//之前自己写的是if（zero.find(ch））
            result+="0";               //当地一个元素的返回值为零时if判断否，因此会出现问题
        if(first.find(ch)!=string::npos)//同时也忘记了姓是存在大小写区分的，这个toUpperCase函数返回char
            result+="1";
        if(second.find(ch)!=string::npos)
            result+="2";
        if(third.find(ch)!=string::npos)
            result+="3";
        if(forth.find(ch)!=string::npos)
            result+="4";
        if(fifth.find(ch)!=string::npos)
            result+="5";
        if(sixth.find(ch)!=string::npos)
            result+="6";

        }
     return result;
    }

STUDENT_TEST("测试编码函数") {
    EXPECT_EQUAL(changeTostring("AbCd"), "0123");
    EXPECT_EQUAL(changeTostring(""), "");
    EXPECT_EQUAL(changeTostring("1234"), "");
}
//3、去掉相邻的重复数字
string combineLetters(string s)
{

  string result;
  for(int i=0;i<s.length();i++)
  {
     if(s[i]==s[i+1])
         continue;
     result+=s[i];
  }
 return result;
}

STUDENT_TEST("测试合并函数") {
    EXPECT_EQUAL(combineLetters("223344"), "234");
    EXPECT_EQUAL(combineLetters(""), "");
    EXPECT_EQUAL(combineLetters("aa11bb22"), "a1b2");
    EXPECT_EQUAL(combineLetters("aa__bb  c''d"), "a_b c'd");
}

//使用姓氏的第一字母替换第一个数字，并转换为大写
string replaceHeader(string s,string name){
    for(int i=0;i<name.length();i++){
        if(isalpha(name[i])){
         s[0]=toUpperCase(name[i]);
         break;
        }
         else
            continue;}
    return s;
  }
STUDENT_TEST("测试替换函数") {
    EXPECT_EQUAL(replaceHeader("", ""), "");
    EXPECT_EQUAL(replaceHeader("01", "mike"), "M1");
}
//删除所有编码数字中的零
/*string deleteZero(string s){
    int len=s.length();
    for(int i=0;i<len;i++){
        if(s[i]=='0')
            s.erase(i,1);
    }
    return s;
}*/
string deleteZero(string s){
    string result;
    for(int i=0;i<s.length();i++){
        if(s[i]=='0'){
            continue;
      }
        else result+=s[i];
    }
    return result;}
 STUDENT_TEST("测试去零函数") {
        EXPECT_EQUAL(deleteZero(""), "");
        EXPECT_EQUAL(deleteZero(" _"), " _");
        EXPECT_EQUAL(deleteZero("0a0b2"), "ab2");
        EXPECT_EQUAL(deleteZero("0100200"), "12");
    }
//通过填充0或者截掉多余的部分
 string  tofour(string s){
     if(s.length()>4)
         return s.erase(4);
         while(s.length()<4)
         {
             s+="0";
         }
         return s;
 }
 STUDENT_TEST("测试调整函数") {
     EXPECT_EQUAL(tofour(""), "0000");
     EXPECT_EQUAL(tofour("12"), "1200");
     EXPECT_EQUAL(tofour("xuehao"), "xueh");
 }
/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
 string soundex(string s) {
     string result;
    result=changeTostring(s);
     result=combineLetters(result);
     result=replaceHeader(result,s);
     result=deleteZero(result);
     result=tofour(result);
     return result;
 }
 STUDENT_TEST("Sample inputs from handout") {
     EXPECT_EQUAL(soundex("Curie"), "C600");
     EXPECT_EQUAL(soundex("O'Conner"), "O256");
 }

 STUDENT_TEST("hanrahan is in lowercase") {
     EXPECT_EQUAL(soundex("hanrahan"), "H565");
 }

 STUDENT_TEST("DRELL is in uppercase") {
     EXPECT_EQUAL(soundex("DRELL"), "D640");
 }

 STUDENT_TEST("Liu has to be padded with zeros") {
     EXPECT_EQUAL(soundex("Liu"), "L000");
 }

 STUDENT_TEST("Tessier-Lavigne has a hyphen") {
     EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
 }

 STUDENT_TEST("Au consists of only vowels") {
     EXPECT_EQUAL(soundex("Au"), "A000");
 }

 STUDENT_TEST("Egilsdottir is long and starts with a vowel") {
     EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
 }

 STUDENT_TEST("Jackson has three adjcaent duplicate codes") {
     EXPECT_EQUAL(soundex("Jackson"), "J250");
 }

 STUDENT_TEST("Schwarz begins with a pair of duplicate codes") {
     EXPECT_EQUAL(soundex("Schwarz"), "S620");
 }

 STUDENT_TEST("Van Niekerk has a space between repeated n's") {
     EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
 }

 STUDENT_TEST("Wharton begins with Wh") {
     EXPECT_EQUAL(soundex("Wharton"), "W635");
 }

 STUDENT_TEST("Ashcraft is not a special case") {
     // Some versions of Soundex make special case for consecutive codes split by hw
     // We do not make this special case, just treat same as codes split by vowel
     EXPECT_EQUAL(soundex("Ashcraft"), "A226");
 }
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name这个提供的代码打开具有给定名称的文件
    // and then reads the lines of that file into a vector.将文件读入一个数组里
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    // The names in the database are now stored in the provided
    // vector named databaseNames

    /* TODO: Fill in the remainder of this function. */
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here


