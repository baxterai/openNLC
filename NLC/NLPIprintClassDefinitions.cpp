/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
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
 * File Name: NLPIprintClassDefinitions.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1e7b 23-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLPIprintClassDefinitions.h"
#include "NLPIprintDefs.h"


/*
class className
{
public:

	className(void);
	~className(void);
	
	string name;
	
	vector<somevar *> somevarPropertyList;	//subclass
	....
	
	vector<somevar *> somevarDefinitionList;	//inherited parents
	
	...
	vector<somevar *> somevarFunctionList;
	...
};
*/
bool printClassDefinitions(vector<NLPIclassDefinition *> * classDefinitionList, int progLang, string * code)
{
	for(vector<NLPIclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{	
		NLPIclassDefinition * classDefinition = *classDefinitionIter;
		
		if(!(classDefinition->isActionOrConditionInstanceNotClass))
		{
			string className = classDefinition->name;
			string classDefinitionEntryText = progLangClassTitlePrepend[progLang] + className;

			#ifdef NLPI_DEBUG
			cout << "printClassDefinitions: className:" << className << endl;
			#endif
			
			bool foundDefinition = false;
			for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
			{
				if(!foundDefinition)
				{
					foundDefinition = true;
					classDefinitionEntryText = classDefinitionEntryText + " : ";
				}
				else
				{
					classDefinitionEntryText = classDefinitionEntryText + ", ";
				}
				NLPIclassDefinition * targetClassDefinition = *localListIter;
				string targetName = targetClassDefinition->name;
				classDefinitionEntryText = classDefinitionEntryText + progLangClassInheritanceHeader[progLang] + targetName;
			}
			printLine(classDefinitionEntryText, 0, code);
			printLine(progLangOpenClass[progLang], 0, code);
			printLine(progLangClassIntro[progLang], 0, code);
			string classConstructorDeclaration = className + progLangClassConstructorDestructorAppend[progLang];
			printLine(classConstructorDeclaration, 1, code);
			string classDestructorDeclaration = progLangClassDestructorPrepend[progLang] + className + progLangClassConstructorDestructorAppend[progLang];
			printLine(classDestructorDeclaration, 1, code);
			//printLine("", 1, code);
			//string classNameCode = progLangClassNameVariableType[progLang] + progLangClassNameVariableName[progLang] + progLangStringOpenClose[progLang] + className + progLangStringOpenClose[progLang] + progLangEndLine[progLang];
			//printLine(classNameCode, 1, code);
			//printLine("", 1, code);

			for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->propertyList.begin(); localListIter != classDefinition->propertyList.end(); localListIter++)
			{
				NLPIclassDefinition * targetClassDefinition = *localListIter;			
				string propertyClassName = targetClassDefinition->name;
				//NLPIitem * param1 = targetClassDefinition->parameters.at(0);	//not required to be used
				string localListDeclarationText = generateCodePropertyListDefinitionText(propertyClassName, progLang) + progLangEndLine[progLang];
				printLine(localListDeclarationText, 1, code);	
			}

			for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->conditionList.begin(); localListIter != classDefinition->conditionList.end(); localListIter++)
			{
				NLPIclassDefinition * targetClassDefinition = *localListIter;
				//string targetName = targetClassDefinition->name;	//condition instance name not used
				NLPIitem * param1 = targetClassDefinition->parameters.at(0);
				string localListDeclarationText = generateCodeConditionListDefinitionText(param1->className, param1->className2, progLang) + progLangEndLine[progLang];
				printLine(localListDeclarationText, 1, code);
			}

			for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->functionList.begin(); localListIter != classDefinition->functionList.end(); localListIter++)
			{
				NLPIclassDefinition * targetClassDefinition = *localListIter;
				string targetName = targetClassDefinition->functionNameSpecial;
				string functionArguments = "";

				generateFunctionArgumentsWithActionConceptInheritanceString(&(targetClassDefinition->parameters), &functionArguments, progLang);
				string localListDeclarationText = progLangClassMemberFunctionType[progLang] + targetName + progLangClassMemberFunctionParametersOpen[progLang] + functionArguments + progLangClassMemberFunctionParametersClose[progLang] + progLangEndLine[progLang];
				printLine(localListDeclarationText, 1, code);
			}
			
			printLine(progLangCloseClass[progLang], 0, code);
			printLine("", 0, code);
		}
	}
}

void generateFunctionArgumentsWithActionConceptInheritanceString(vector<NLPIitem*> * parameters, string * functionArguments, int progLang)
{
	for(vector<NLPIitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		//do: ADD: if(functionArgumentCertified);
		NLPIitem * currentItem = *parametersIterator;
		/*
		cout << "\tcurrentItem->itemType = " << currentItem->itemType << endl;
		cout << "currentItem->className = " << currentItem->className << endl;
		cout << "currentItem->instanceName = " << currentItem->instanceName << endl;
		*/
		if(currentItem->itemType == NLPI_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodePluralDefinitionText(currentItem, progLang);
		}
		#ifdef NLPI_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		else if(currentItem->itemType == NLPI_ITEM_TYPE_FUNCTION)		
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularDefinitionText(currentItem, progLang);
		}
		#endif
		else if(currentItem->itemType == NLPI_ITEM_TYPE_FUNCTION_OBJECT)		
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularDefinitionText(currentItem, progLang);
		}
		#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		else if(currentItem->itemType == NLPI_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeConditionPairDefinitionText(currentItem, progLang);
		}
		else if(currentItem->itemType == NLPI_ITEM_TYPE_FUNCTION_ARGUMENT_PROPERTY)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularDefinitionText(currentItem, progLang);
		}
		#endif
	}
}

string generateCodePluralDefinitionText(NLPIitem * currentItem, int progLang)
{
	string pluralClassName = currentItem->className;
	string pluralInstanceName = currentItem->instanceName;
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
	if(currentItem->functionArgumentPassCastRequired)
	{
		pluralClassName = currentItem->functionArgumentPassCastClassName;
	}
	#endif	
	string codePluralDefinitionText = progLangClassListTypeStart[progLang] + pluralClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang]+ STRING_SPACE + pluralClassName + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION;	
	return codePluralDefinitionText;
}

string generateCodeSingularDefinitionText(NLPIitem * currentItem, int progLang)
{	
	string singularClassName = currentItem->className;
	string singularInstanceName = currentItem->instanceName;
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
	if(currentItem->functionArgumentPassCastRequired)
	{
		singularClassName = currentItem->functionArgumentPassCastClassName;
	}
	#endif	
	string codeSingularDefinitionText = singularClassName + progLangPointer[progLang] + STRING_SPACE + singularInstanceName;
	return codeSingularDefinitionText;
}

#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
string generateCodeConditionPairDefinitionText(NLPIitem * currentItem, int progLang)
{
	string conditionClassName = currentItem->className;
	string conditionObjectClassName = currentItem->className2;
	#ifdef NLPI_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeConditionListDefinitionText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + STRING_SPACE + conditionClassName + NLPI_ITEM_TYPE_CONDITIONPAIRVAR_APPENDITION;
	#else
	string codeConditionListDefinitionText = progLangClassPairTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang]+ STRING_SPACE + generateConditionPairName(conditionClassName, conditionObjectClassName);				
	#endif
	return codeConditionListDefinitionText;
}
#endif


