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
 * File Name: NLCitemClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1f2a 10-December-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/




#include "NLCitemClass.h"
#include "GIAtranslatorOperations.h"



NLCitem::NLCitem(void)
{
	itemType = NLC_ITEM_INSTANCE_ID_UNDEFINED;
	className = "";
	instanceName = "";
	functionName = "";
	className2 = "";
	instanceName2 = "";
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = "";
	formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
	#endif
}
NLCitem::NLCitem(GIAentityNode * entity, int newItemType)
{
	itemType = newItemType;
	className = generateClassName(entity);
	instanceName = generateInstanceName(entity);
	functionName = generateFunctionName(entity);	//added 9 November 2013
	className2 = "";
	instanceName2 = "";
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = "";
	formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
	#endif
}
NLCitem::NLCitem(string newName, int newItemType)
{
	itemType = newItemType;
	className = generateClassName(newName);	//changed 9 November 2013
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	instanceName = newName;		//added 21 November 2013
	#else
	instanceName = ""
	#endif
	functionName = generateFunctionName(newName);	//added 9 November 2013
	className2 = "";
	instanceName2 = "";
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = "";
	formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
	#endif
}
NLCitem::NLCitem(NLCitem * newItem)
{
	itemType = newItem->itemType;
	className = newItem->className;
	instanceName = newItem->instanceName;
	functionName = newItem->functionName;
	className2 = newItem->className2;
	instanceName2 = newItem->instanceName2;
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = newItem->functionArgumentPassCastClassName;
	formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = newItem->formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias;;
	#endif
}
NLCitem::~NLCitem(void)
{
}

string generateClassName(GIAentityNode * entity)
{
	string className = generateClassName(entity->entityName);
	return className;
}
string generateClassName(string entityName)
{
	string className = entityName + NLC_CLASS_NAME_APPEND;
	return className;
}
string generateFunctionName(GIAentityNode * entity)
{
	return generateFunctionName(entity->entityName);
}
string generateFunctionName(string entityName)
{
	string functionName = entityName + NLC_FUNCTION_NAME_APPEND;
	return functionName;
}
string generateInstanceName(GIAentityNode * entity)
{
	string instanceName = entity->entityName + convertLongToString(entity->idInstance);
	return instanceName;
}

string convertLongToString(long number)
{
	//return to_string(number);	//C++11
	
	char tempString[100];
	sprintf(tempString, "%ld", number);
	return string(tempString);
}

