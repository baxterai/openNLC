/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction. This does not imply such arrangements
 * do not constitute derivative works.
 *
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCpreprocessor.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1g17a 17-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCpreprocessor.h"
#include "GIAentityNodeClass.h" //required for GIA_NLP_START_SENTENCE_INDEX

NLCsentence::NLCsentence(void)
{
	sentenceContents = "";
	sentenceIndex = 0;
	indentation = 0;
	next = NULL;
}
NLCsentence::~NLCsentence(void)
{
}

NLCfunction::NLCfunction(void)
{
	functionName = "";
	firstNLCsentenceInFunction = new NLCsentence();
	next = NULL;
}
NLCfunction::~NLCfunction(void)
{
}


bool preprocessTextForNLC(string inputFileName, NLCfunction * firstNLCfunctionInList, bool * detectedFunctions, int * numberOfInputFilesInList, vector<string> * inputTextFileNameList)
{
	*numberOfInputFilesInList = 1;
	
	bool result = true;
	ifstream parseFileObject(inputFileName.c_str());
	if(!parseFileObject.rdbuf( )->is_open( ))
	{
		//txt file does not exist in current directory.
		cout << "Error: NLC input file does not exist in current directory: " << inputFileName << endl;
		result = false;
	}
	else
	{
		NLCfunction * currentNLCfunctionInList = firstNLCfunctionInList;
		NLCsentence * currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
		char currentToken;
		int sentenceIndex = GIA_NLP_START_SENTENCE_INDEX;
		int currentIndentation = 0;
		bool parsingIndentation = true;
		int lineWordIndex = 0;
		bool parsingFunctionName = false;
		string functionName = "";
		*detectedFunctions = false;
		string functionContents = "";
		string sentenceContents = "";
		
		while(parseFileObject.get(currentToken))
		{
			cout << currentToken;
			
			#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
			//extract functions from file and generate separate files
			if(parsingFunctionName)
			{
				if(currentToken == CHAR_NEWLINE)
				{
					cout << "start function: functionName = " << functionName << endl;
					inputTextFileNameList->push_back(functionName);
					functionContents = "";
					sentenceContents = "";
					currentIndentation = 0;
					lineWordIndex = 0;
					parsingFunctionName = false;
				}
				else
				{
					functionName = functionName + currentToken;
				}
			}
			else
			{
			#endif
				if(currentToken == CHAR_NEWLINE)
				{
					//assume that a sentence has already been created based on a full stop (do not support multiline sentences)
					parsingIndentation = true;
					currentIndentation = 0;
					lineWordIndex = 0;
				}
				else if(currentToken == CHAR_FULLSTOP)
				{
					parsingIndentation = false;
					cout << "create new sentence" << endl;
					cout << "sentenceContents = " << sentenceContents + currentToken << endl;
					currentNLCsentenceInList->sentenceContents = sentenceContents + currentToken;	//append the fullstop
					currentNLCsentenceInList->sentenceIndex = sentenceIndex;
					currentNLCsentenceInList->indentation = currentIndentation;
					currentNLCsentenceInList->next = new NLCsentence();
					currentNLCsentenceInList = currentNLCsentenceInList->next;
					sentenceContents = "";
					sentenceIndex++;
					lineWordIndex++;
				}
				else if(currentToken == NLC_PREPROCESSOR_INDENTATION_CHAR)
				{
					if(parsingIndentation)
					{
						currentIndentation++;
					}
					else
					{
						cout << "preprocessTextForNLC() warning: NLC_INDENTATION_CHAR detected and !parsingIndentation" << endl;
						sentenceContents = sentenceContents + currentToken;
					}
					lineWordIndex++;
				}
				else if(currentToken == NLC_PREPROCESSOR_FUNCTION_HEADER_MID_CHAR)
				{
					parsingIndentation = false;
					#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
					if(sentenceContents == NLC_PREPROCESSOR_FUNCTION_HEADER_STRING)
					{
						if(*detectedFunctions)
						{
							functionContents = functionContents.substr(0, functionContents.length() - sentenceContents.length());
							cout << "create new function = " << functionName << endl;
							cout << "functionContents = " << functionContents << endl;
							writeStringToFile(functionName, functionContents);
							cout << "end function: functionName = " << functionName << endl;
							currentNLCfunctionInList->functionName = functionName;
							currentNLCfunctionInList->next = new NLCfunction();
							currentNLCfunctionInList = currentNLCfunctionInList->next;
							currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
							functionName = "";
							*numberOfInputFilesInList = *numberOfInputFilesInList+1;
							//create new function file based on current text
						}
						else
						{
							cout << "detectedFunctions" << endl;
							*detectedFunctions = true;
						}
						parsingFunctionName = true;
					}
					else
					{
					#endif
						sentenceContents = sentenceContents + currentToken;
					#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
					}
					#endif
					lineWordIndex++;
				}
				else
				{
					parsingIndentation = false;
					sentenceContents = sentenceContents + currentToken;
					lineWordIndex++;
				}
				functionContents = functionContents + currentToken;
			#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
			}
			#endif	
		}
		#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
		if(*detectedFunctions)
		{
			//create a final function based on the final text..
			cout << "create new function = " << functionName << endl;
			cout << "functionContents = " << functionContents << endl;
			writeStringToFile(functionName, functionContents);
			//create new function file based on current text
		}
		#endif
	}
	

	return result;
}


void writeStringToFile(string fileName, string s)
{
	ofstream writeFileObject(fileName);

	for(int i=0; i < s.size(); i++)
	{
		writeFileObject.put(s[i]);
	}

	writeFileObject.close();
}




