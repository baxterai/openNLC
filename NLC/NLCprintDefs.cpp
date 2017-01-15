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
 * File Name: NLCprintDefs.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1j14b 13-September-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/

#include "NLCprintDefs.h"

void printLine(string command, int level, string * code)
{
	//if(command != "")
	//{
	string line = "";
	for(int i=0; i<level; i++)
	{
		line = line + CHAR_TAB;
	}
	line = line + command;
	line = line + CHAR_NEWLINE;
	*code = *code + line;
	//}
}

string generatePropertyListName(string propertyInstanceName)
{
	string propertyListName = propertyInstanceName + NLC_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION;
	return propertyListName;
}

string generatePropertyLocalListName(NLCitem * param)
{
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
		string instanceName = param->instanceName;
		#ifdef NLC_USE_ORIGINAL_INSTANCE_LIST_NAMES
		string propertyListName = instanceName + NLC_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION;
		#else
		string propertyListName = instanceName + NLC_ITEM_TYPE_INSTANCEVAR_APPENDITION + NLC_ITEM_TYPE_LISTVAR_APPENDITION;	
		#endif
	#else
		string className = param->className;
		string propertyListName = className + NLC_ITEM_TYPE_LISTVAR_APPENDITION;		
	#endif
	return propertyListName;
}

string generateGenericListName(string genericObjectName, string genericListAppendName)
{
	#ifdef NLC_USE_ORIGINAL_INSTANCE_LIST_NAMES
	string propertyListName = genericObjectName + genericListAppendName + NLC_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION;
	#else
	string propertyListName = genericObjectName + genericListAppendName + NLC_ITEM_TYPE_LISTVAR_APPENDITION;
	#endif
	return propertyListName;
}

string generateConditionListName(string conditionClassName, string conditionObjectClassName)
{
	string conditionListName = conditionClassName + conditionObjectClassName + NLC_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION;
	return conditionListName;
}

string generateConditionPairDefinitionName(string conditionClassName, string conditionObjectClassName)
{
	string conditionListName = conditionClassName + conditionObjectClassName + NLC_ITEM_TYPE_CONDITIONPAIRVAR_APPENDITION;
	return conditionListName;
}

string generateCodePropertyListDefinitionText(string propertyClassName, int progLang)
{
	string codePropertyListDefinitionText = generateCodePropertyListDefinitionTypeText(propertyClassName, progLang) + propertyClassName + NLC_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION;
	return codePropertyListDefinitionText;
}

string generateCodePropertyListDefinitionTypeText(string propertyClassName, int progLang)
{
	string codePropertyListDefinitionText = progLangClassListTypeStart[progLang] + propertyClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];
	return codePropertyListDefinitionText;
}

string generateCodeConditionListDefinitionText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeConditionListDefinitionText = generateCodeConditionListDefinitionTypeText(conditionClassName, conditionObjectClassName, progLang) + conditionClassName + NLC_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION;
	#else
	string codeConditionListDefinitionText = generateCodeConditionListDefinitionTypeText(conditionClassName, conditionObjectClassName, progLang) + generateConditionListName(conditionClassName, conditionObjectClassName);
	#endif
	return codeConditionListDefinitionText;
}
string generateCodeConditionListDefinitionTypeText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeConditionListDefinitionText = progLangClassList2DTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];
	#else
	string codeConditionListDefinitionText = progLangClassList2DTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];
	#endif
	return codeConditionListDefinitionText;
}

#ifdef NLC_GENERATE_TYPE_LISTS
string generateCodePropertyListDefinitionTypeText2(string propertyClassName, int progLang)
{
	string codePropertyListDefinitionText = progLangClassListTypeStart[progLang] + progLangClassListTypeStart[progLang] + propertyClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang] + progLangClassListTypeEnd[progLang];
	return codePropertyListDefinitionText;
}
#endif

string generateTempVariableName(NLCitem * param, int progLang)
{
	string tempVariableName = param->className + progLangPointer[progLang] + STRING_SPACE + param->instanceName;
	return tempVariableName;
}
