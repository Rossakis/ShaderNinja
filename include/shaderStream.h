#include <iostream>
#include <fstream>
#include <string>

class ShaderStream {
    public: 
    
    //Returns the specified shader file as an array of characters
    static const std::string readShaderFile(const char* shaderFileName){
        std::ifstream shaderFile (shaderFileName);
        std::string outputString = "";
        
        if(shaderFile.is_open()){
            std::string line = "";

            while(std::getline(shaderFile, line)){
                outputString += line + '\n';
            }
            
            shaderFile.close(); 
        }
         else 
            std::cerr << "Error opening file: " << shaderFileName << std::endl;
    

        return outputString;
    };
};