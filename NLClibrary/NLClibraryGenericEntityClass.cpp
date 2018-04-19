/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryGenericEntityClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2f8b 18-April-2018
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryGenericEntityClass.hpp"

NLCgenericEntityClass::NLCgenericEntityClass(void)
{
	name = "NLCgenericEntity";
	#ifdef NLC_MATH_OBJECTS
	mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN;
	mathObjectNumericalValue = INT_DEFAULT_VALUE;
	#ifdef NLC_MATH_OBJECTS_ADVANCED
	#ifdef NLC_MATH_OBJECTS_STRING
	mathObjectStringValue = "";
	#endif
	#ifdef NLC_MATH_OBJECTS_BOOLEAN
	mathObjectBooleanValue = false;
	#endif
	#endif
	#endif
	#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
	inverseConditionTwoWay = false;
	#endif
		
	#ifdef NLC_ENUM_LISTS 
	enumType = NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM;
	#endif
	
	#ifdef NLC_API
	thirdpartyAPIobject = NULL;
	#endif
};

#ifdef NLC_ENUM_LISTS
#ifdef NLC_ENUM_LISTS_PROPERTIES
unordered_map<string, string> enumTypeTableProperties;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#ifdef NLC_ENUM_LISTS_CONDITIONS
unordered_map<string, string> enumTypeTableConditions;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#ifdef NLC_ENUM_LISTS_ACTIONS
unordered_map<string, string> enumTypeTableActions;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#endif


#ifdef NLC_REDEFINITIONS
//must embed this function in NLCprintCodeBlocks.cpp code;
bool checkParentClassName(NLCgenericEntityClass* object, string className)
{
	bool result = false;
	if(object->name == className)
	{
		result = true;
	}
	for(vector<NLCgenericEntityClass*>::iterator iter1 = object->parentClassList.begin(); iter1 < object->parentClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* parent = *iter1;
		if(checkParentClassName(parent, className))
		{
			result = true;
		}
	}
	return result;
}
#endif
#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
void addEntityToReferenceContextList(vector<NLCgenericEntityClass*>& referenceContextList, NLCgenericEntityClass* NLCgenericEntity, int sentenceIndex)
{
	referenceContextList.push_back(NLCgenericEntity);
	NLCgenericEntity->lastSentenceReferenced.push(sentenceIndex);
}

void clearReferenceContextList(vector<NLCgenericEntityClass*>& referenceContextList)
{
	for(vector<NLCgenericEntityClass*>::iterator iter1 = referenceContextList.begin(); iter1 < referenceContextList.end(); iter1++) 
	{
		NLCgenericEntityClass* NLCgenericEntity = *iter1;
		NLCgenericEntity->lastSentenceReferenced.pop();
	}
	referenceContextList.clear();
}
#endif


#ifdef NLC_ENUM_LISTS
#ifdef NLC_ENUM_LISTS_PROPERTIES
string calculateEnumTypeProperty(string entityName)
{
	string enumType = NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM;
	unordered_map<string, string>::iterator enumTypeTablePropertiesIter = enumTypeTableProperties.find(entityName);
	if(enumTypeTablePropertiesIter != enumTypeTableProperties.end())
	{
		enumType = enumTypeTablePropertiesIter->second;
	}
	return enumType;
}
#endif
#ifdef NLC_ENUM_LISTS_CONDITIONS
string calculateEnumTypeCondition(string entityName)
{
	string enumType = NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM;
	unordered_map<string, string>::iterator enumTypeTableConditionsIter = enumTypeTableConditions.find(entityName);
	if(enumTypeTableConditionsIter != enumTypeTableConditions.end())
	{
		enumType = enumTypeTableConditionsIter->second;
	}
	return enumType;
}
#endif
#endif


#ifdef NLC_MATH_OBJECTS_ADVANCED

#ifdef NLC_MATH_OBJECTS_ADVANCED_DYNAMIC_DETERMINE_MATH_OBJECT_VARIABLE_TYPE
void detectMathObjectVariableType(NLCgenericEntityClass* object, double* mathObjectVariableNumericalPointer, string* mathObjectVariableStringPointer, bool* mathObjectVariableBooleanPointer, int* sentenceMathObjectVariableType)
{
	*sentenceMathObjectVariableType = object->mathObjectType;
	*mathObjectVariableNumericalPointer = object->mathObjectNumericalValue;
	*mathObjectVariableStringPointer = object->mathObjectStringValue;
	*mathObjectVariableBooleanPointer = object->mathObjectBooleanValue;
}
#endif

void assignMathObjectValue(NLCgenericEntityClass* targetObject, NLCgenericEntityClass* sourceObject)
{
	if(sourceObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
	{
		targetObject->mathObjectNumericalValue = sourceObject->mathObjectNumericalValue;
	}
	else if(sourceObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING)
	{
		targetObject->mathObjectStringValue = sourceObject->mathObjectStringValue;
	}
	else if(sourceObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN)
	{
		targetObject->mathObjectBooleanValue = sourceObject->mathObjectBooleanValue;
	}
	else
	{
		cout << "assignMathObjectValue{} error: assigning mathobject value but mathObjectType set to NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN for source object; sourceObject->name = " << sourceObject->name << endl; 
	}
}
void assignMathObjectValue(NLCgenericEntityClass* targetObject, double sourceObjectNumerical)
{	
	targetObject->mathObjectNumericalValue = sourceObjectNumerical;
	targetObject->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
}
#ifdef NLC_MATH_OBJECTS_STRING
void assignMathObjectValue(NLCgenericEntityClass* targetObject, string sourceObjectString)
{	
	targetObject->mathObjectStringValue = sourceObjectString;
	targetObject->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING;
}
#endif
#ifdef NLC_MATH_OBJECTS_BOOLEAN
void assignMathObjectValue(NLCgenericEntityClass* targetObject, bool sourceObjectBoolean)
{	
	targetObject->mathObjectBooleanValue = sourceObjectBoolean;
	targetObject->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN;
}
#endif

#ifdef NLC_MATH_OBJECTS_ADVANCED_ASSIGN_MATHTEXT_VALUE_FUNCTION
void assignMathTextValue(double* targetObject, NLCgenericEntityClass* sourceObject)
{
	if(sourceObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
	{
		*targetObject = sourceObject->mathObjectNumericalValue;
	}
	else
	{
		cout << "assignMathTextValue{} error: assignMathTextValue to double targetObject and sourceObject mathObjectType != NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL); sourceObject->name = " << sourceObject->name << endl; 	
	}
}
#ifdef NLC_MATH_OBJECTS_STRING
void assignMathTextValue(string* targetObject, NLCgenericEntityClass* sourceObject)
{
	if(sourceObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING)
	{
		*targetObject = sourceObject->mathObjectStringValue;
	}
	else
	{
		cout << "assignMathTextValue{} error: assignMathTextValue to string targetObject and sourceObject mathObjectType != NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING); sourceObject->name = " << sourceObject->name << endl; 	
	}
}
#endif
#ifdef NLC_MATH_OBJECTS_BOOLEAN
void assignMathTextValue(bool* targetObject, NLCgenericEntityClass* sourceObject)
{
	if(sourceObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN)
	{
		*targetObject = sourceObject->mathObjectBooleanValue;
	}
	else
	{
		cout << "assignMathTextValue{} error: assignMathTextValue to bool targetObject and sourceObject mathObjectType != NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN); sourceObject->name = " << sourceObject->name << endl; 	
	}
}
#endif
#else
double getMathObjectValue(NLCgenericEntityClass* targetObject)
{
	if(targetObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
	{
		return targetObject->mathObjectNumericalValue;
	}
	else
	{
		cout << "getMathObjectValue{} error: getMathObjectValue from mathObjectNumericalValue and targetObject mathObjectType != NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL); targetObject->name = " << targetObject->name << endl; 	
	}
}
#ifdef NLC_MATH_OBJECTS_STRING
string getMathObjectValue(NLCgenericEntityClass* targetObject)
{
	if(targetObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING)
	{
		return targetObject->mathObjectStringValue;
	}
	else
	{
		cout << "getMathObjectValue{} error: getMathObjectValue from mathObjectStringValue and targetObject mathObjectType != NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING); targetObject->name = " << targetObject->name << endl; 	
	}
}
#endif
#ifdef NLC_MATH_OBJECTS_BOOLEAN
bool getMathObjectValue(NLCgenericEntityClass* targetObject)
{
	if(targetObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN)
	{
		return targetObject->mathObjectBooleanValue;
	}
	else
	{
		cout << "getMathObjectValue{} error: getMathObjectValue from mathObjectBooleanValue and targetObject mathObjectType != NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN); targetObject->name = " << targetObject->name << endl; 	
	}	
}
#endif
#endif

#ifndef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
#ifdef NLC_MATH_OBJECTS_ADVANCED_ADDITIONS
NLCgenericEntityClass* addMathObjectValue(NLCgenericEntityClass* objectA, NLCgenericEntityClass* objectB)
{
	NLCgenericEntityClass* newEntity = new NLCgenericEntityClass();
	if((objectA->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL) && (objectB->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL))
	{
		newEntity->mathObjectNumericalValue = objectA->mathObjectNumericalValue + objectB->mathObjectNumericalValue;
		newEntity->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
	}
	#ifdef NLC_MATH_OBJECTS_STRING
	else if((objectA->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING) && (objectB->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING))
	{
		newEntity->mathObjectStringValue = objectA->mathObjectStringValue + objectB->mathObjectStringValue;
		newEntity->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING;
	}
	#endif
	else
	{
		cout << "addMathObjectValue{} error: adding mathobject value but no numerical or string value found for both objects; objectA->name = " << objectA->name << ", objectB->name = " << objectB->name << endl; 
	}
	return newEntity;
	
}
NLCgenericEntityClass* addMathObjectValue(double objectA, NLCgenericEntityClass* objectB)
{
	NLCgenericEntityClass* newEntity = new NLCgenericEntityClass();
	if(objectB->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
	{
		newEntity->mathObjectNumericalValue = objectA + objectB->mathObjectNumericalValue;
		newEntity->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
	}
	else
	{
		cout << "addMathObjectValue{} error: addMathObjectValue and objectB mathObjectType != NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL); objectB->name = " << objectB->name << endl; 	
	}
	return newEntity;
}
NLCgenericEntityClass* addMathObjectValue(NLCgenericEntityClass* objectA, double objectB)
{
	NLCgenericEntityClass* newEntity = new NLCgenericEntityClass();
	if(objectA->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
	{
		newEntity->mathObjectNumericalValue = objectA->mathObjectNumericalValue + objectB;
		newEntity->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
	}
	else
	{
		cout << "addMathObjectValue{} error: addMathObjectValue and objectA mathObjectType != NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL); objectA->name = " << objectA->name << endl; 	
	}
	return newEntity;
}
NLCgenericEntityClass* addMathObjectValue(double objectA, double objectB)
{
	NLCgenericEntityClass* newEntity = new NLCgenericEntityClass();
	newEntity->mathObjectNumericalValue = objectA + objectB;
	newEntity->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
	return newEntity;
}
#ifdef NLC_MATH_OBJECTS_STRING
NLCgenericEntityClass* addMathObjectValue(string objectA, NLCgenericEntityClass* objectB)
{
	NLCgenericEntityClass* newEntity = new NLCgenericEntityClass();
	if(objectB->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING)
	{
		newEntity->mathObjectStringValue = objectA + objectB->mathObjectStringValue;
		newEntity->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING;
	}
	else
	{
		cout << "addMathObjectValue{} error: addMathObjectValue and objectB mathObjectType != NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING); objectB->name = " << objectB->name << endl;	
	}
	return newEntity;
}
NLCgenericEntityClass* addMathObjectValue(NLCgenericEntityClass* objectA, string objectB)
{
	NLCgenericEntityClass* newEntity = new NLCgenericEntityClass();
	if(objectA->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING)
	{
		newEntity->mathObjectStringValue = objectA->mathObjectStringValue + objectB;
		newEntity->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING;
	}
	else
	{
		cout << "addMathObjectValue{} error: addMathObjectValue and objectA mathObjectType != NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING); objectA->name = " << objectA->name << endl;	
	}
	return newEntity;
}
NLCgenericEntityClass* addMathObjectValue(string objectA, string objectB)
{
	NLCgenericEntityClass* newEntity = new NLCgenericEntityClass();
	newEntity->mathObjectStringValue = objectA + objectB;
	newEntity->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING;
	return newEntity;
}
#endif
#endif
#ifdef NLC_MATH_OBJECTS_ADVANCED_COMPARISONS
bool testMathObjectValue(NLCgenericEntityClass* targetObject, NLCgenericEntityClass* sourceObject)
{
	bool testResult = false;
	int mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN;
	if(sourceObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
	{
		if(targetObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
		{
			mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
			testResult = testMathObjectValue(sourceObject->mathObjectNumericalValue, targetObject->mathObjectNumericalValue);
		}
		else
		{
			cout << "testMathObjectValue{} error: testing mathobject value but no numerical value found for target object; sourceObject->name = " << sourceObject->name << ", targetObject->name = " << targetObject->name << endl; 
		}
	}
	#ifdef NLC_MATH_OBJECTS_STRING
	else if(sourceObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING)
	{
		if(targetObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING)
		{
			mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING;
			testResult = testMathObjectValue(sourceObject->mathObjectStringValue, targetObject->mathObjectStringValue);
			
		}
		else
		{
			cout << "testMathObjectValue{} error: testing mathobject value but no string value found for target object; sourceObject->name = " << sourceObject->name << ", targetObject->name = " << targetObject->name << endl; 	
		}
	}
	#endif
	#ifdef NLC_MATH_OBJECTS_BOOLEAN
	else if(sourceObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN)
	{
		if(targetObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN)
		{
			mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING;
			testResult = testMathObjectValue(sourceObject->mathObjectBooleanValue, targetObject->mathObjectBooleanValue);
			
		}
		else
		{
			cout << "testMathObjectValue{} error: testing mathobject value but no boolean value found for target object; sourceObject->name = " << sourceObject->name << ", targetObject->name = " << targetObject->name << endl; 	
		}
	}
	#endif
	else
	{
		cout << "testMathObjectValue{} error: testing mathobject value but no numerical, string, or boolean value found for source object; sourceObject->name = " << sourceObject->name << ", targetObject->name = " << targetObject->name << endl; 
	}
	return testResult;
}
//NB supported testExpression values: NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST/NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN/NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN/NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN_OR_EQUAL_TO/NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN_OR_EQUAL_TO/NLC_PREPROCESSOR_MATH_OPERATOR_DOES_NOT_EQUAL
bool testMathObjectValue(NLCgenericEntityClass* targetObject, double sourceObject)
{
	bool testResult = false;
	if(targetObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
	{
		testResult = testMathObjectValue(targetObject->mathObjectNumericalValue, sourceObject);
	}
	else
	{
		cout << "testMathObjectValue{} error: testing mathobject value but no numerical value found for target object; targetObject->name = " << targetObject->name << endl; 	
		testResult = false;
	}
	return testResult;
}
bool testMathObjectValue(double targetObject, NLCgenericEntityClass* sourceObject)
{
	bool testResult = false;
	if(sourceObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
	{
		testResult = testMathObjectValue(targetObject, sourceObject->mathObjectNumericalValue);
	}
	else
	{
		cout << "testMathObjectValue{} error: testing mathobject value but no numerical value found for source object; sourceObject->name = " << sourceObject->name << endl; 	
		testResult = false;
	}
	return testResult;
}
bool testMathObjectValue(double targetObject, double sourceObject)
{
	bool testResult = (targetObject == sourceObject);
	return testResult;					
}
#ifdef NLC_MATH_OBJECTS_STRING
//NB supported testExpression values: NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST
bool testMathObjectValue(NLCgenericEntityClass* targetObject, string sourceObject)
{
	bool testResult = false;
	if(targetObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING)
	{
		testResult = testMathObjectValue(targetObject->mathObjectStringValue, sourceObject);
	}
	else
	{
		cout << "testMathObjectValue{} error: testing mathobject value but no string value found for target object; targetObject->name = " << targetObject->name << endl; 	
		testResult = false;
	}
	return testResult;
}
bool testMathObjectValue(string targetObject, NLCgenericEntityClass* sourceObject)
{
	bool testResult = false;
	if(sourceObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING)
	{
		testResult = testMathObjectValue(targetObject, sourceObject->mathObjectStringValue);
	}
	else
	{
		cout << "testMathObjectValue{} error: testing mathobject value but no string value found for source object; sourceObject->name = " << sourceObject->name << endl; 	
		testResult = false;
	}
	return testResult;
}
bool testMathObjectValue(string targetObject, string sourceObject)
{
	bool testResult = (targetObject == sourceObject);
	return testResult;					
}
#endif
#ifdef NLC_MATH_OBJECTS_BOOLEAN
bool testMathObjectValue(NLCgenericEntityClass* targetObject, bool sourceObject)
{
	bool testResult = false;
	if(targetObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN)
	{
		testResult = testMathObjectValue(targetObject->mathObjectBooleanValue, sourceObject);
	}
	else
	{
		cout << "testMathObjectValue{} error: testing mathobject value but no boolean value found for target object; targetObject->name = " << targetObject->name << endl; 	
		testResult = false;
	}
	return testResult;
}
bool testMathObjectValue(bool targetObject, NLCgenericEntityClass* sourceObject)
{
	bool testResult = false;
	if(sourceObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN)
	{
		testResult = testMathObjectValue(targetObject, sourceObject->mathObjectBooleanValue);
	}
	else
	{
		cout << "testMathObjectValue{} error: testing mathobject value but no boolean value found for source object; sourceObject->name = " << sourceObject->name << endl; 	
		testResult = false;
	}
	return testResult;
}
bool testMathObjectValue(bool targetObject, bool sourceObject)
{
	bool testResult = (targetObject == sourceObject);
	return testResult;					
}
bool testMathObjectValue(NLCgenericEntityClass* object)
{
	//boolean expression, eg "the red button" (theredbutton)
	//note boolean statement expressions are not parsed by testMathObjectValue eg if(testMathObjectValue(theredchickenisnexttothehouse)), they are parsed directly eg if(theredchickenisnexttothehouse)
	bool testResult = false;
	if(object->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN)
	{
		testResult = object->mathObjectBooleanValue;
	}
	else
	{
		cout << "testMathObjectValue{} error: testing mathobject value but no boolean value found for object; object->name = " << object->name << endl; 		
	}
	return testResult;
}
#endif
#endif
#endif

#endif

#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_FUNCTION
void verifyDefiniteReferenceExistence(bool empty, string entityName, string genericListAppendName)
{
	if(empty)
	{
		string warningMessage = string(NLC_RUNTIME_ERROR_PREPEND) + genericListAppendName + string(NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_WARNING_TEXT_APPEND) + entityName;
		cout << warningMessage << endl;
	}
}
#endif
