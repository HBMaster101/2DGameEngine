////////////////////////////////////////////
//File:              <TextFileReader.cpp>
//Author:            <Hunter Bergerud>
//Date Created:      <3/3/14>
//Date Modified:     <3/3/14>
//Brief:             <Text File Reader Code>
////////////////////////////////////////////
#include "TextFileReader.h"
std::string textFileReader(const char* a_szFileName) 
{
    //Make a string that stores the file's contents
    std::string FileContents;
	//Make a ifstring that stores what the file streams
	std::ifstream FileStream;
	//Open a FileStream that has the required data
	FileStream.open(a_szFileName, std::ios::in);
	//If the FileStream is open
	if (FileStream.is_open()) 
	{
		//Make a string called Line with nothing in it
        std::string Line = "";
			//While calling getLine with the required data
			while(getline(FileStream,Line))
				//Have FileContents add Line to itself
				FileContents += "\n" + Line;
			//Close FileStream
			FileStream.close();
    }
	//Else
	else
	{
		//Print out an Error telling the user the program failed to open the file
		printf("Error: Failed to open file '%s'!\n",a_szFileName);
	}
	//Return FileContents
	return FileContents;
}