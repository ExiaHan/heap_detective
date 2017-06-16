#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

const std::string DEFAULT_DELIMITER = " \t\v\n\r\f=";
class Tokenizer
{
public:
    Tokenizer();
    Tokenizer(const std::string& str, const std::string& delimiter=DEFAULT_DELIMITER);
    ~Tokenizer();
    void set(const std::string& str, const std::string& delimiter=DEFAULT_DELIMITER);
    void setString(const std::string& str);             
    void setDelimiter(const std::string& delimiter);    
    std::string next();                                 
 
protected:

private:
    void skipDelimiter();                              
    bool isDelimiter(char c);                          

    std::string buffer;                                 
    std::string token;                                  
    std::string delimiter;                              
    std::string::const_iterator currPos;           

};

#endif 
