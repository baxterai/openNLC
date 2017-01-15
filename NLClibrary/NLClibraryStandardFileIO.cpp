/*******************************************************************************
 *
 * This file is part of NLC.
 *
 * NLC is commercially licensed software. It may not be redistributed,
 * and may only be used by a registered licensee.
 *
 * NLC is sold in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * BAI Commercial License for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You will have received a copy of the BAI Commercial License
 * along with NLC. For more information, visit <http://www.baxterai.com>
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryStandardFileIO.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q8a 20-August-2015
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "../NLClibrary/NLClibraryStandardFileIO.hpp"
#include "../NLClibrary/NLClibraryStandardOperations.hpp"
#include "../NLCgenerated/NLCgenerated.hpp"
#include "../source/SHAREDvars.h"	//required for convertStringToDouble
//need to update to support .csv file io (not just xml file io)

//writeFunction() limitation: only supports NLC_USE_ADVANCED_REFERENCING (not GIA_USE_ADVANCED_REFERENCING)
void writeFunction(vector<NLCgenericEntityClass*>& writeClassList, vector<NLCgenericEntityClass*>& writeObjectClassList)
{
	bool result = true;
	
	for(vector<NLCgenericEntityClass*>::iterator iter1 = writeClassList.begin(); iter1 < writeClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* writeAction = *iter1;
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityToConditionList = getConditionListByConditionName(writeAction, NLC_USE_LIBRARY_FILEIO_FUNCTION_ACTION_CONDITION_TO_NAME); 

		if(NLCgenericEntityToConditionList != NULL)
		{
			for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter2 = NLCgenericEntityToConditionList->begin(); iter2 != NLCgenericEntityToConditionList->end(); iter2++)
			{
				NLCgenericEntityClass* toConditionObject = iter2->second;
				if(toConditionObject->name == NLC_USE_LIBRARY_FILEIO_FUNCTION_ACTIONOBJECT_FILE_NAME)
				{
					#ifdef NLC_DEBUG_LIBRARY
					cout << "writeFunction() pass" << endl;
					#endif
					int fileType = NLC_USE_LIBRARY_FILEIO_FILETYPE_DEFAULT;
					string delimiter = NLC_USE_LIBRARY_FILEIO_FLAT_DELIMITER_DEFAULT;
					string fileName = "";
					if(!(toConditionObject->aliasList.empty()))
					{
						fileName = toConditionObject->aliasList.back();	//eg write the People to the file called People.xml
						if(fileName.find(NLC_USE_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_APPEND_XML) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
						{
							fileType = NLC_USE_LIBRARY_FILEIO_FILETYPE_XML;
						}
						else if(fileName.find(NLC_USE_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_APPEND_CSV) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
						{
							fileType = NLC_USE_LIBRARY_FILEIO_FILETYPE_FLAT;
							delimiter = NLC_USE_LIBRARY_FILEIO_FLAT_DELIMITER_COMMA;
						}
						else if(fileName.find(NLC_USE_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_APPEND_TXT) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
						{
							fileType = NLC_USE_LIBRARY_FILEIO_FILETYPE_FLAT;
							delimiter = NLC_USE_LIBRARY_FILEIO_FLAT_DELIMITER_TAB;
						}
					}
					else
					{
						fileName = string(NLC_USE_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_PREPEND) + (writeObjectClassList.back())->name + string(NLC_USE_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_APPEND_XML);	//eg write the People to the file (generate file name NLCfileIOPeople.xml)
					}
					
					if(fileType == NLC_USE_LIBRARY_FILEIO_FILETYPE_XML)
					{
						XMLparserTag* firstTagInXMLFile = new XMLparserTag();
						writeXMLfilePropertyList(firstTagInXMLFile, &writeObjectClassList);
 						if(!writeXMLfile(fileName, firstTagInXMLFile))
 						{
							result = false;
						}
					}
					else if(fileType == NLC_USE_LIBRARY_FILEIO_FILETYPE_FLAT)
					{//csv
						//write to flat file - property lists only
 						if(!writeNLCflatFilePropertyLists(fileName, &writeObjectClassList, delimiter))
 						{
							result = false;
						}
					}
				}
			}
		}
		else
		{
			cout << "move() error: write action 'to' condition not found" << endl;
		}
	}
}

#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_PROPERTY_LISTS
void writeXMLfilePropertyList(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList)
{
	writeXMLfileVectorList(firstTagInList, writeObjectClassList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_PROPERTY_LIST);
}
void writeXMLfileVectorList(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList, string listName)
{
	if(!(writeObjectClassList->empty()))
	{
		#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
		XMLparserTag* currentTagInList = createVectorListTagWithLowerLevel(firstTagInList, listName, writeObjectClassList);
		#else
		XMLparserTag* currentTagInList = firstTagInList;	//CHECKTHIS
		#endif
		for(vector<NLCgenericEntityClass*>::iterator iter1 = writeObjectClassList->begin(); iter1 < writeObjectClassList->end(); iter1++) 
		{
			NLCgenericEntityClass* writeObject = *iter1;
			#ifdef NLC_DEBUG_LIBRARY
			cout << "writeXMLfileObject(): writeObject->name = " << writeObject->name << endl;
			#endif

			writeXMLfileObject(currentTagInList, writeObject);
		}
	}
}
#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
XMLparserTag* createVectorListTagWithLowerLevel(XMLparserTag* currentTagInList, string tagName, vector<NLCgenericEntityClass*>* vectorClassList)
{
	currentTagInList->name = tagName;
	currentTagInList->firstAttribute->name = NLC_USE_LIBRARY_FILEIO_XML_ATTRIBUTENAME_LISTNAME;
	currentTagInList->firstAttribute->value = (vectorClassList->back())->name;
	currentTagInList->firstAttribute->nextAttribute = new XMLParserAttribute();
	currentTagInList->nextTag = new XMLparserTag();
	currentTagInList->firstLowerLevelTag = new XMLparserTag();
	currentTagInList = currentTagInList->firstLowerLevelTag;
	return currentTagInList;
}
#endif
#endif

#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_CONDITION_LISTS
void writeXMLfileConditionListRecurse(XMLparserTag* firstTagInList, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* writeObjectClassMapList)
{
	writeXMLfileMapList(firstTagInList, writeObjectClassList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_CONDITION_LIST);
}
void writeXMLfileMapList(XMLparserTag* firstTagInList, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* writeObjectClassMapList, string listName)
{
	if(!(writeObjectClassMapList.empty())
	{
		#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
		XMLparserTag* currentTagInList = createMapListTagWithLowerLevel(firstTagInList, listName, writeObjectClassMapList);
		#else
		XMLparserTag* currentTagInList = firstTagInList;	//CHECKTHIS
		#endif
		for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter1 = writeObjectClassMapList.begin(); iter1 < writeObjectClassMapList.end(); iter1++) 
		{
			writeObject = (iter2)->second;
			#ifdef NLC_DEBUG_LIBRARY
			cout << "writeXMLfileObject(): writeObject->name = " << writeObject->name << endl;
			#endif
			
			currentTagInList->firstAttribute->name = NLC_USE_LIBRARY_FILEIO_XML_ATTRIBUTENAME_CONDITION
			currentTagInList->firstAttribute->value = (iter2)->first->name;		//write condition name
			currentTagInList->firstAttribute->nextAttribute  = new XMLparserAttribute(); 
			writeXMLfileObject(currentTagInList, writeObject);
		}
	}
}
#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
XMLparserTag* createMapListTagWithLowerLevel(XMLparserTag* currentTagInList, string tagName, NLCgenericEntityClass*>* writeObjectClassMapList)
{
	currentTagInList->name = tagName;
	
	XMLparserAttribute* currentAttribute = currentTagInList->firstAttribute;
	string mapListName1 = writeObjectClassMapList.begin()->first->name;
	string mapListName2 = writeObjectClassMapList.begin()->second->name;
	currentAttribute->name = NLC_USE_LIBRARY_FILEIO_XML_ATTRIBUTENAME_MAPLISTNAME1
	currentTagInList->firstAttribute->value = mapListName1;
	currentAttribute->nextAttribute = new XMLparserAttribute();
	currentAttribute = currentAttribute->nextAttribute
	currentAttribute->name = NLC_USE_LIBRARY_FILEIO_XML_ATTRIBUTENAME_MAPLISTNAME2
	currentTagInList->firstAttribute->value = mapListName2;
	currentAttribute->nextAttribute = new XMLparserAttribute();
	
	currentTagInList->nextTag = new XMLparserTag();
	currentTagInList->firstLowerLevelTag = new XMLparserTag();
	currentTagInList = currentTagInList->firstLowerLevelTag;
	return currentTagInList;
}
#endif
#endif

#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_ACTION_LISTS
void writeXMLfileActionListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList)
{
	writeXMLfileVectorList(firstTagInList, writeObjectClassList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTION_LIST);
}
void writeXMLfileActionIncomingListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList)
{
	writeXMLfileVectorList(firstTagInList, writeObjectClassList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONINCOMING_LIST);
}
void writeXMLfileActionSubjectListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList)
{
	writeXMLfileVectorList(firstTagInList, writeObjectClassList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONSUBJECT_LIST);
}
void writeXMLfileActionObjectListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList)
{
	writeXMLfileVectorList(firstTagInList, writeObjectClassList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONOBJECT_LIST);
}
#endif






void writeXMLfileObject(XMLparserTag* firstTagInList, NLCgenericEntityClass* writeObject)
{
	XMLparserTag* currentTagInList = firstTagInList;
	currentTagInList->name = writeObject->name;
	currentTagInList->nextTag = new XMLparserTag();
	currentTagInList = currentTagInList->nextTag;

	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_PROPERTY_LISTS
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	currentTagInList = createAllListTagWithLowerLevel(currentTagInList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_PROPERTY_LIST_ALL);
	#endif
	for(unordered_map<string, vector<NLCgenericEntityClass*>  *>::iterator iter2 = writeObject->propertyLists.begin(); iter2 != writeObject->propertyLists.end(); iter2++)
	{
		string propertyListKey = iter2->first;
		vector<NLCgenericEntityClass*>* propertyList = iter2->second;

		currentTagInList->firstLowerLevelTag = new XMLparserTag();
		writeXMLfilePropertyList(currentTagInList->firstLowerLevelTag, propertyList);
	}
	#endif
	
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_CONDITION_LISTS
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	currentTagInList = createAllListTagWithLowerLevel(currentTagInList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_CONDITION_LIST_ALL);
	#endif
	for(unordered_map<pair<string, string>, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>  *>::iterator iter2 = writeObject->conditionLists.begin(); iter2 != writeObject->conditionLists.end(); iter2++)
	{
		pair<string, string>* conditionListKey = iter2->first;
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = iter2->second;

		currentTagInList->firstLowerLevelTag = new XMLparserTag();
		writeXMLfileConditionList(currentTagInList->firstLowerLevelTag, propertyList);
	}
	#endif
	
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_ACTION_LISTS
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	currentTagInList = createAllListTagWithLowerLevel(currentTagInList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTION_LIST_ALL);
	#endif
	for(unordered_map<string, vector<NLCgenericEntityClass*>  *>::iterator iter2 = writeObject->propertyLists.begin(); iter2 != writeObject->propertyLists.end(); iter2++)
	{
		string propertyListKey = iter2->first;
		vector<NLCgenericEntityClass*>* propertyList = iter2->second;

		currentTagInList->firstLowerLevelTag = new XMLparserTag();
		writeXMLfileActionList(currentTagInList->firstLowerLevelTag, propertyList);
	}
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	currentTagInList = createAllListTagWithLowerLevel(currentTagInList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONINCOMING_LIST_ALL);
	#endif
	for(unordered_map<string, vector<NLCgenericEntityClass*>  *>::iterator iter2 = writeObject->actionIncomingLists.begin(); iter2 != writeObject->actionIncomingLists.end(); iter2++)
	{
		string propertyListKey = iter2->first;
		vector<NLCgenericEntityClass*>* propertyList = iter2->second;

		currentTagInList->firstLowerLevelTag = new XMLparserTag();
		writeXMLfileActionIncomingList(currentTagInList->firstLowerLevelTag, propertyList);
	}
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	currentTagInList = createAllListTagWithLowerLevel(currentTagInList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONSUBJECT_LIST_ALL);
	#endif
	for(unordered_map<string, vector<NLCgenericEntityClass*>  *>::iterator iter2 = writeObject->actionSubjectLists.begin(); iter2 != writeObject->actionSubjectLists.end(); iter2++)
	{
		string propertyListKey = iter2->first;
		vector<NLCgenericEntityClass*>* propertyList = iter2->second;

		currentTagInList->firstLowerLevelTag = new XMLparserTag();
		writeXMLfileActionSubjectList(currentTagInList->firstLowerLevelTag, propertyList);
	}
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	currentTagInList = createAllListTagWithLowerLevel(currentTagInList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONOBJECT_LIST_ALL);
	#endif
	for(unordered_map<string, vector<NLCgenericEntityClass*>  *>::iterator iter2 = writeObject->actionObjectLists.begin(); iter2 != writeObject->actionObjectLists.end(); iter2++)
	{
		string propertyListKey = iter2->first;
		vector<NLCgenericEntityClass*>* propertyList = iter2->second;

		currentTagInList->firstLowerLevelTag = new XMLparserTag();
		writeXMLfileActionObjectList(currentTagInList->firstLowerLevelTag, propertyList);
	}
	#endif
}

#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
XMLparserTag* createAllListTagWithLowerLevel(XMLparserTag* currentTagInList, string tagName)
{
	currentTagInList->name = tagName;
	currentTagInList->nextTag = new XMLparserTag();
	currentTagInList->firstLowerLevelTag = new XMLparserTag();
	currentTagInList = currentTagInList->firstLowerLevelTag;
	return currentTagInList;
}
#endif


/*
//consider creating an alias "get"/"add"/"read" eg "get/add/read the people from People.xml"
void getFunction(vector<moveClass*> &getClassList, vector<NLCgenericEntityClass*> &getObjectClassList)
{
	readFunction(getClassList, getObjectClassList)	
}
void addFunction(vector<moveClass*> &addClassList, vector<NLCgenericEntityClass*> &addObjectClassList)
{
	readFunction(addClassList, addObjectClassList)	
}
*/
void readFunction(vector<NLCgenericEntityClass*>& readClassList, vector<NLCgenericEntityClass*>& readObjectClassList)	
{
	bool result = true;
	for(vector<NLCgenericEntityClass*>::iterator iter1 = readClassList.begin(); iter1 < readClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* readAction = *iter1;
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityFromConditionList = getConditionListByConditionName(readAction, NLC_USE_LIBRARY_FILEIO_FUNCTION_ACTION_CONDITION_FROM_NAME); 

		if(NLCgenericEntityFromConditionList != NULL)
		{
			for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter2 = NLCgenericEntityFromConditionList->begin(); iter2 != NLCgenericEntityFromConditionList->end(); iter2++)
			{
				NLCgenericEntityClass* fromConditionObject = iter2->second;
				if(fromConditionObject->name == NLC_USE_LIBRARY_FILEIO_FUNCTION_ACTIONOBJECT_FILE_NAME)
				{
					#ifdef NLC_DEBUG_LIBRARY
					cout << "writeFunction() pass" << endl;
					#endif
					
					int fileType = NLC_USE_LIBRARY_FILEIO_FILETYPE_DEFAULT;
					string delimiter = NLC_USE_LIBRARY_FILEIO_FLAT_DELIMITER_DEFAULT;
					string fileName = "";
					if(!(fromConditionObject->aliasList.empty()))
					{
						fileName = fromConditionObject->aliasList.back();	//eg write the People to the file called People.xml
						if(fileName.find(NLC_USE_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_APPEND_XML) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
						{
							fileType = NLC_USE_LIBRARY_FILEIO_FILETYPE_XML;
						}
						else if(fileName.find(NLC_USE_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_APPEND_CSV) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
						{
							fileType = NLC_USE_LIBRARY_FILEIO_FILETYPE_FLAT;
						}
						else if(fileName.find(NLC_USE_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_APPEND_TXT) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
						{
							fileType = NLC_USE_LIBRARY_FILEIO_FILETYPE_FLAT;
							delimiter = NLC_USE_LIBRARY_FILEIO_FLAT_DELIMITER_TAB;
						}
					}
					else
					{
						fileName = string(NLC_USE_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_PREPEND) + (readObjectClassList.back())->name + string(NLC_USE_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_APPEND_XML);	//eg write the People to the file (generate file name NLCfileIOPeople.xml)
					}
					
					if(fileType == NLC_USE_LIBRARY_FILEIO_FILETYPE_XML)
					{
						XMLparserTag* firstTagInXMLFile = new XMLparserTag();
 						if(!readXMLfile(fileName, firstTagInXMLFile))
 						{
							result = false;
						}
						if(!readXMLfileToNLCpropertyLists(firstTagInXMLFile, &readObjectClassList))
						{
							result = false;
						}
					}
					else if(fileType == NLC_USE_LIBRARY_FILEIO_FILETYPE_FLAT)
					{//csv
						//read from flat file - property lists only
 						if(!readNLCflatfilePropertyLists(fileName, &readObjectClassList, delimiter))
 						{
							result = false;
						}
					}
				}
			}
		}
		else
		{
			cout << "move() error: write action 'to' condition not found" << endl;
		}
	}
}
bool readXMLfileToNLCpropertyLists(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList)
{
	bool result = true;
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	if(firstTagInList->name == NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_PROPERTY_LIST)	//redundant
	{
	#endif
		if(!readXMLfilePropertyList(firstTagInList, readObjectClassList))
		{
			result = false;
		}
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	}
	else
	{
		cout << "readXMLfile error: propertyList tag not detected";
		result = false;
	}
	#endif
	return result;
}						

#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_PROPERTY_LISTS
bool readXMLfilePropertyList(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList)
{
	bool result = true;
	if(!readXMLfileVectorList(firstTagInList, readObjectClassList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_PROPERTY_LIST))
	{
		result = false;
	}
	return result;
}
bool readXMLfileVectorList(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList, string listName)
{
	bool result = true;
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	if(firstTagInList->name == listName)
	{
	#endif
		XMLparserTag* currentTagInVectorList = firstTagInList->firstLowerLevelTag;
		while(currentTagInVectorList->nextTag != NULL)
		{
			NLCgenericEntityClass* readObject = generateObjectByName(currentTagInVectorList->name);			
			/*
			readObjectClassList.push_back(readObject);
			if(currentTagInVectorList->firstLowerLevelTag != NULL)
			{
			readXMLfileObject(currentTagInVectorList->firstLowerLevelTag, readObject);
			}
			*/
			readXMLfileObject(currentTagInVectorList, readObject);
			currentTagInVectorList = currentTagInVectorList->nextTag;
		}
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	}
	else
	{
		cout << "readXMLfileVectorList error: " << listName << " tag not detected";
		result = false;
	}
	#endif
}
#endif

#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_CONDITION_LISTS
bool readXMLfileConditionListRecurse(XMLparserTag* firstTagInList, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* readObjectClassMapList)
{
	return readXMLfileMapList(firstTagInList, writeObjectClassList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_CONDITION_LIST);
}
bool readXMLfileMapList(XMLparserTag* firstTagInList, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* readObjectClassMapList, string listName)
{
	bool result = true;
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	if(firstTagInList->name == listName)
	{
	#endif
		XMLparserTag* currentTagInVectorList = firstTagInList->firstLowerLevelTag;
		while(currentTagInVectorList->nextTag != NULL)
		{
			NLCgenericEntityClass* readObject = generateObjectByName(currentTagInVectorList->name);
			if(currentTagInVectorList->firstAttributeInTag != NULL)
			{
				if(currentTagInVectorList->firstAttributeInTag->name == NLC_USE_LIBRARY_FILEIO_XML_ATTRIBUTENAME_CONDITION)
				{
					NLCgenericEntityClass* readObjectCondition = generateObjectByName(currentTagInVectorList->firstAttribute->value);
					readObjectClassMapList->insert(pair<NLCgenericEntityClass*, NLCgenericEntityClass*>(readObjectCondition, readObject));	//CHECKTHIS: check can insert as NLCgenericEntityClass and not their specificObjectClassName
				}
				else
				{
					cout << "readXMLfileMapList error: firstAttributeInTag->name != 'condition'" << endl;
					result = false;	
				}
			}
			else
			{
				cout << "readXMLfileMapList error: firstAttributeInTag tag not detected";
				result = false;	
			}
			
			/*
			if(currentTagInVectorList->firstLowerLevelTag != NULL)
			{
				readXMLfileObject(currentTagInVectorList->firstLowerLevelTag, readObject);
			}
			*/
			readXMLfileObject(currentTagInVectorList, readObject);
			currentTagInVectorList = currentTagInVectorList->nextTag;
		}
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	}
	else
	{
		cout << "readXMLfileMapList error: " << listName << " tag not detected";
		result = false;
	}
	#endif
	return result;
}
#endif

#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_ACTION_LISTS
void readXMLfileActionListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList)
{
	readXMLfileVectorList(firstTagInList, readObjectClassList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTION_LIST);
}
void readXMLfileActionIncomingListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList)
{
	readXMLfileVectorList(firstTagInList, readObjectClassList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONINCOMING_LIST);
}
void readXMLfileActionSubjectListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList)
{
	readXMLfileVectorList(firstTagInList, readObjectClassList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONSUBJECT_LIST);
}
void readXMLfileActionObjectListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList)
{
	readXMLfileVectorList(firstTagInList, readObjectClassList, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONOBJECT_LIST);
}
#endif


void readXMLfileObject(XMLparserTag* firstTagInList, NLCgenericEntityClass* readObject)
{
	/*
	#ifndef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS	//yet to code this
	if(firstTagInList
	vector<NLCgenericEntityClass*>* propertyList = getPropertyListByName(readObject, propertyListName);
	readXMLfilePropertyList(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList)
	
	void readXMLfilePropertyList(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList)

	#else
	*/
	
	XMLparserTag* currentTagInList = firstTagInList->firstLowerLevelTag;
	while(currentTagInList->nextTag != NULL)
	{		
		#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_PROPERTY_LISTS
		readFileObjectVectorListAll(currentTagInList, readObject, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_PROPERTY_LIST_ALL, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_PROPERTY_LIST);
		#endif

		#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_CONDITION_LISTS
		readFileObjectMapListAll(currentTagInList, readObject, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_CONDITION_LIST_ALL, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_CONDITION_LIST);
		#endif

		#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_ACTION_LISTS
		readFileObjectVectorListAll(currentTagInList, readObject, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTION_LIST_ALL, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTION_LIST);
		readFileObjectVectorListAll(currentTagInList, readObject, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONINCOMING_LIST_ALL, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONINCOMING_LIST);
		readFileObjectVectorListAll(currentTagInList, readObject, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONSUBJECT_LIST_ALL, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONSUBJECT_LIST);
		readFileObjectVectorListAll(currentTagInList, readObject, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONOBJECT_LIST_ALL, NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONOBJECT_LIST);
		#endif
	
		currentTagInList = currentTagInList->nextTag;
	}
}


bool readFileObjectVectorListAll(XMLparserTag* currentTagInList, NLCgenericEntityClass* readObject, string vectorListAllTagName, string vectorListTagName)
{
	bool result = true;
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	if(currentTagInList->name == vectorListAllTagName)
	{
		XMLparserTag* currentTagInVectorListAll = currentTagInList->firstLowerLevelTag;
		while(currentTagInVectorListAll->nextTag != NULL)
		{
			if(currentTagInVectorListAll->name == vectorListTagName)
			{
				string vectorListName = "";
				if(currentTagInVectorListAll->firstAttribute->name == NLC_USE_LIBRARY_FILEIO_XML_ATTRIBUTENAME_LISTNAME)
				{
					vectorListName = currentTagInVectorListAll->firstAttribute->value;
				}
				else
				{
					cout << "readXMLfileObject error(): " << vectorListTagName << ": currentTagInVectorListAll->firstAttribute->name != NLC_USE_LIBRARY_FILEIO_XML_ATTRIBUTENAME_LISTNAME" << endl;
					result = false;
				}

				vector<NLCgenericEntityClass*>* vectorList = NULL;
				if(vectorListTagName == NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_PROPERTY_LIST)
				{
					vectorList = getPropertyListByName(readObject, vectorListName);
				}
				else if(vectorListTagName == NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTION_LIST)
				{
					vectorList = getActionListByName(readObject, vectorListName);
				}
				else if(vectorListTagName == NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONINCOMING_LIST)
				{
					vectorList = getActionIncomingListByName(readObject, vectorListName);
				}
				else if(vectorListTagName == NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONOBJECT_LIST)
				{
					vectorList = getActionObjectListByName(readObject, vectorListName);
				}
				else if(vectorListTagName == NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONSUBJECT_LIST)
				{
					vectorList = getActionSubjectListByName(readObject, vectorListName);
				}												
	#endif
				readXMLfileVectorList(currentTagInVectorListAll, vectorList, vectorListTagName);
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
			}
			currentTagInVectorListAll = currentTagInVectorListAll->nextTag;	
		}
	}
	#endif
	return result;
}

#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_CONDITION_LISTS
bool readFileObjectMapListAll(XMLparserTag* currentTagInList, NLCgenericEntityClass* readObject, string mapListAllTagName, string mapListTagName)
{
	bool result = true;
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	if(currentTagInList->name == mapListAllTagName)
	{
		XMLparserTag* currentTagInMapListAll = currentTagInList->firstLowerLevelTag;
		while(currentTagInMapListAll->nextTag != NULL)
		{
			if(currentTagInMapListAll->name == mapListTagName)
			{
				string mapListName1 = "";
				if(currentTagInMapListAll->firstAttribute->name == NLC_USE_LIBRARY_FILEIO_XML_ATTRIBUTENAME_LISTNAME)
				{
					mapListName1 = currentTagInMapListAll->firstAttribute->value;
				}
				else
				{
					cout << "readXMLfileObject error(): " << mapListTagName << ": currentTagInMapListAll->firstAttribute->name != NLC_USE_LIBRARY_FILEIO_XML_ATTRIBUTENAME_LISTNAME" << endl;
					result = false;
				}
				string mapListName2 = "";
				if(currentTagInMapListAll->firstAttribute->nextAttribute != NULL)
				{
					mapListName2 = currentTagInMapListAll->firstAttribute->nextAttribute->value;
				}	
				else
				{
					cout << "readXMLfileObject error(): " << mapListTagName << ": currentTagInMapListAll->firstAttribute->nextAttribute == NULL" << endl;
					result = false;
				}
				unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* mapList = NULL;
				if(mapListTagName == NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_CONDITION_LIST)
				{
					mapList = getMapListByMapName(readObject, mapListName1, mapListName2);
				}
	#endif
				readXMLfileMapList(currentTagInMapListAll, mapList);
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
				}
			}
			currentTagInMapListAll = currentTagInMapListAll->next;		
		}
	}
	#endif
	return result;
}
#endif


//limitation; 3D lists not currently supported (ie childObjects cannot be plural lists)
bool writeNLCflatFilePropertyLists(string fileName, vector<NLCgenericEntityClass*>* writeObjectClassList, string delimiter)
{
	bool result = true;
	
	string fileContents = "";
	bool firstLineWriteHeader = true;
	bool lineIndex = 1;
	for(vector<NLCgenericEntityClass*>::iterator iter1 = writeObjectClassList->begin(); iter1 < writeObjectClassList->end(); iter1++) 
	{
		NLCgenericEntityClass* parentObject = *iter1;
		if(firstLineWriteHeader)
		{
			string fileHeader = "";
			bool firstRow = true;
			for(unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator iter2 = parentObject->propertyLists.begin(); iter2 != parentObject->propertyLists.end(); iter2++) 
			{
				if(!firstRow)
				{
					fileHeader = fileHeader + delimiter;
				}
				string variableName = iter2->first;
				vector<NLCgenericEntityClass*>* childObjectList = iter2->second;
				NLCgenericEntityClass* childObject = childObjectList->back();	//limitation; 3D lists not currently supported (ie childObjects cannot be plural lists)
				fileHeader = fileHeader + childObject->name;
				firstRow = false;
			}
			fileContents = fileContents + fileHeader + STRING_NEW_LINE;
			firstLineWriteHeader = false;
			lineIndex++;
		}
		bool firstRow = false;
		string fileLine = "";
		for(unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator iter2 = parentObject->propertyLists.begin(); iter2 != parentObject->propertyLists.end(); iter2++) 
		{
			if(!firstRow)
			{
				fileLine = fileLine + delimiter;
			}
			string variableName = iter2->first;
			vector<NLCgenericEntityClass*>* childObjectList = iter2->second;
			if(!(childObjectList->empty()))
			{
				NLCgenericEntityClass* childObject = childObjectList->back();	//limitation; 3D lists not currently supported (ie childObjects cannot be plural lists)
				if(!(childObject->aliasList.empty()))
				{
					string value = childObject->aliasList.back();
					fileLine = fileLine + value;
				}
				else
				{
					string value = to_string(childObject->value);
					fileLine = fileLine + value;
				}
			}
			else
			{
				fileLine = fileLine + NLC_USE_LIBRARY_FILEIO_FLAT_NULL_PROPERTY_VALUE;
			}
			firstRow = false;
		}
		fileContents = fileContents + fileLine + STRING_NEW_LINE;
		lineIndex++;
	}
		
	writeStringToFile(fileName, &fileContents);
	
	return result;
}

//readNLCflatfilePropertyLists() limitation: data cells containing both alpha and numeric (eg variable1) is not allowed; as anything containing numeric will currently be treated as numeric 
bool readNLCflatfilePropertyLists(string fileName, vector<NLCgenericEntityClass*>* readObjectClassList, string delimiter)
{
	bool result = true;
	
	ifstream parseFileObject(fileName.c_str());
	if(!parseFileObject.rdbuf()->is_open())
	{
		//file does not exist in current directory.
		cout << "readNLCflatfilePropertyLists() error: input file does not exist in current directory: " << fileName << endl;
		result = false;
	}
	else
	{
		int lineIndex = 1;
		string currentLine;
		if(getline(parseFileObject, currentLine))
		{	
			string delimiter = NLC_USE_LIBRARY_FILEIO_FLAT_DELIMITER_DEFAULT;
			for(int i=0; i<NLC_USE_LIBRARY_FILEIO_FLAT_NUMBER_OF_DELIMITERS; i++)
			{
				if(currentLine.find(nlcLibraryFileIOflatFileDelimiters[i]) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
				{
					delimiter = nlcLibraryFileIOflatFileDelimiters[i];
					if(delimiter != NLC_USE_LIBRARY_FILEIO_FLAT_DELIMITER_DEFAULT)
					{
						cout << "readNLCflatfilePropertyLists() warning: reading " << fileName << " file and found delimiter: " << delimiter << endl;
					}
				}
			}

			//read header...
			vector<string> headerVariableList;

			bool foundHeader = true;
			int currentIndexInHeader = 0;
			bool stillFindingColumns = true;
			while(stillFindingColumns)
			{
				string currentVariableName = "";
				int nextIndexInHeader = currentLine.find(delimiter, currentIndexInHeader);
				if(nextIndexInHeader == CPP_STRING_FIND_RESULT_FAIL_VALUE)
				{
					stillFindingColumns = false;
					currentVariableName = currentLine.substr(currentIndexInHeader, currentLine.length()-currentIndexInHeader);
				}
				else
				{
					currentVariableName = currentLine.substr(currentIndexInHeader, nextIndexInHeader-currentIndexInHeader);
				}	
				
				if(variableNameIsAcceptableNLCclassName(currentVariableName))
				{
					#ifdef NLC_DEBUG_LIBRARY
					cout << "readNLCflatfilePropertyLists() reading header; currentVariableName = " << currentVariableName << endl;
					#endif		
					headerVariableList.push_back(currentVariableName);
					currentIndexInHeader = nextIndexInHeader+1;
				}
				else
				{
					#ifdef NLC_ALLOW_ALPHANUMERIC_CLASS_NAMES
					cout << "readNLCflatfilePropertyLists() error: reading " << fileName << " file and header variable does not contain alphabetic characters: " << currentVariableName << endl;
					#else
					cout << "readNLCflatfilePropertyLists() error: reading " << fileName << " file and header variable contains numeric characters:" << currentVariableName << endl;
					#endif
					foundHeader = false;
					result = false;
				}
			}
			
			if(foundHeader)	//NB if there is no header and each variable only contains letters, then NLC will fail to parse the file (it will treat the first line as the header)
			{
				int numberOfVariables = headerVariableList.size();
				
				//read contents...
				while(getline(parseFileObject, currentLine))
				{
					lineIndex++;
					vector<string> lineVariableList;
					int currentIndexInContents = 0;
					for(int i=0; i<numberOfVariables; i++)
					{
						string currentVariable = "";
						int nextIndexInContents = currentLine.find(delimiter, currentIndexInContents);
						if(nextIndexInContents == CPP_STRING_FIND_RESULT_FAIL_VALUE)
						{
							stillFindingColumns = false;
							currentVariable = currentLine.substr(currentIndexInContents, currentLine.length()-currentIndexInContents);
						}
						else
						{
							currentVariable = currentLine.substr(currentIndexInContents, nextIndexInContents-currentIndexInContents);
						}
						#ifdef NLC_DEBUG_LIBRARY
						cout << "readNLCflatfilePropertyLists() reading line; currentVariable = " << currentVariable << endl;
						#endif
						lineVariableList.push_back(currentVariable);
						currentIndexInContents = nextIndexInContents+1;
					}
					
					if(lineVariableList.size() == numberOfVariables)
					{	
						NLCgenericEntityClass* parentObject = readObjectClassList->back();	//assume parent object list has at least one variable already (defined by NLC); use this as the first variable to be filled
						string parentObjectName = parentObject->name;	
						bool firstParentObjectIeRowInContent = true;
													
						vector<string>::iterator iter1 = headerVariableList.begin();
						vector<string>::iterator iter2 = lineVariableList.begin();
						for(int i=0; i<numberOfVariables; i++)
						{
							string variableName = *iter1;
							string variableValue = *iter2;
							
							NLCgenericEntityClass* readObject = generateObjectByName(variableName);
							if(stringContainsNumbers(variableValue) && !stringContainsAlphabetic(variableValue))
							{
								readObject->value = convertStringToDouble(variableValue);
							}
							else
							{
								readObject->aliasList.push_back(variableValue);	//CHECKTHIS
							}

							vector<NLCgenericEntityClass*>* propertyList = getPropertyListByName(parentObject, variableName);	
							if(propertyList != NULL)
							{
								//IMPORTANT: drop data if fail to find the required property list (eg when reading in variables that are never used by user NLC code) 
								cout << "readNLCflatfilePropertyLists() warning: " << parentObjectName << " does not contain a " << variableName << " property list (eg reading a property which is never used by user NLC code). Dropping data." << endl;
							}
							else
							{
								propertyList->push_back(readObject);
							}

							
							if(!firstParentObjectIeRowInContent)
							{
								readObjectClassList->push_back(parentObject);
								parentObject = generateObjectByName(parentObjectName);	//create a new parent object for next row
							}
							else
							{
								firstParentObjectIeRowInContent = false;
							}
							
							#ifdef NLC_DEBUG_LIBRARY
							cout << "readNLCflatfilePropertyLists() reading cell; variableName = " << variableName << ", variableValue = " << variableValue << endl;
							#endif

							iter1++;
							iter2++;
						}
					}
					else
					{
						cout << "readNLCflatfilePropertyLists() error: reading " << fileName << " file and (lineVariableList.size() != headerVariableList.size()), lineIndex = " << lineIndex << endl;
						result = false;
					}
				}
			}
		}
		else
		{
			cout << "readNLCflatfilePropertyLists() error: reading " << fileName << " file; file only has one line (no header or contents detected)" << endl;
			result = false;
		}
	}
		
	return result;
}

bool variableNameIsAcceptableNLCclassName(string currentVariableName)
{
	bool result = false;
	#ifdef NLC_ALLOW_ALPHANUMERIC_CLASS_NAMES
	if(stringContainsAlphabetic(currentVariableName))
	#else
	if(!stringContainsNumbers(currentVariableName))
	#endif
	{
		result = true;
	}
}
			
bool stringContainsNumbers(string s)
{
	bool result = false;
	for(int i=0; i<NLC_USE_LIBRARY_FILEIO_FLAT_NUMBER_OF_NUMERICAL_CHARACTERS; i++)
	{
		if(s.find(nlcLibraryFileIOflatFileNumericalCharacters[i]) == CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			result = true;
		}	
	}
	return result;
}		

bool stringContainsAlphabetic(string s)
{
	bool result = false;
	for(int i=0; i<NLC_USE_LIBRARY_FILEIO_FLAT_NUMBER_OF_ALPHABETIC_CHARACTERS; i++)
	{
		if(s.find(nlcLibraryFileIOflatFileAlphabeticCharacters[i]) == CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			result = true;
		}	
	}
	return result;
}	
