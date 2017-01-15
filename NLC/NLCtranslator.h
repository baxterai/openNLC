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
 * File Name: NLCtranslator.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1w3b 14-January-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR
#define HEADER_NLC_TRANSLATOR

#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "NLCglobalDefs.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"
//#ifdef NLC_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.h"	//required for NLCfunction
#include "NLCtranslatorCodeBlocks.h"
#include "NLCtranslatorCodeBlocksLogicalConditionsAdvanced.h"	//required for tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced
#include "NLCtranslatorClassDefinitions.h"
#include "GIAtranslatorDefs.h"
#include "NLCtranslatorCodeBlocksOperations.h"	//required for initialiseFunctionAliasClassList()
//#endif

#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
class NLClogicalConditionConjunctionContainer
{
public:

	NLClogicalConditionConjunctionContainer(void);
	NLClogicalConditionConjunctionContainer(GIAentityNode* entity);
	~NLClogicalConditionConjunctionContainer(void);

	GIAentityNode* entity;
	vector<NLClogicalConditionConjunctionContainer*> nextConditionConjunctions;
	int optimumPathIndex;
};
#endif

class NLCtranslatorClass
{
	private: NLCtranslatorCodeBlocksClass NLCtranslatorCodeBlocks;
	private: NLCtranslatorCodeBlocksLogicalConditionsAdvancedClass NLCtranslatorCodeBlocksLogicalConditionsAdvanced;
	private: NLCtranslatorClassDefinitionsClass NLCtranslatorClassDefinitions;
	private: SHAREDvarsClass SHAREDvars;
	private: NLCcodeBlockClassClass NLCcodeBlockClass;
	private: NLCclassDefinitionClassClass NLCclassDefinitionClass;
	private: NLCitemClassClass NLCitemClass;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	public: bool translateNetwork(NLCcodeblock* firstCodeBlockInTree, vector<NLCclassDefinition*>* classDefinitionList, vector<GIAentityNode*>* entityNodesActiveListComplete, map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, const int maxNumberSentences, string NLCfunctionName, NLCfunction* currentNLCfunctionInList, const bool useNLCpreprocessor);
	/*
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_ENFORCE
	#ifdef NLC_PREPROCESSOR
	bool identifyImplicitPluralLogicalConditionOperationsObjects(vector<GIAentityNode*>* entityNodesActiveListComplete, int maxNumberSentences);
	#endif
	#endif
	*/
	#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
		private: bool removeRedundantConditionConjunctions(map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, const int maxNumberSentences);
			private: int addConjunctionsConnectedToConditionConjunctionObject(GIAentityNode* conditionEntity, NLClogicalConditionConjunctionContainer* logicalConditionConjunctionContainer, const int sentenceIndex);
			private: bool traceConditionConjunctionsOptimiumPathAndSeeIfConditionConjunctionEntityIsOnIt(NLClogicalConditionConjunctionContainer* logicalConditionConjunctionContainer, const GIAentityNode* logicalConditionConjunctionToTest);
	#endif
		private: bool identifyAndTagAllLogicalConditionOperations(map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, const int maxNumberSentences);
	#else
		private: bool disableAllForLoopPredeterminers(map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, const int maxNumberSentences);
	#endif
	/*
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	bool addFunctionDependenciesWithoutOwners(vector<GIAentityNode*>* entityNodesActiveListComplete, int maxNumberSentences, NLCclassDefinitionFunctionDependency* parentFunctionDependencies, vector<NLCclassDefinitionFunctionDependency*>* functionDependencyList);
	#endif
	*/

#ifdef NLC_INPUT_FUNCTION_LISTS
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	public: void reconcileFunctionDefinitionClassDefinitionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(NLCcodeblock* firstCodeBlockInTree, vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* functionDefinitionClassDefinition);
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
		private: void addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionArgumentsToFunctionDefinition(vector<NLCitem*>* functionDefinitionSourceArgumentList, NLCclassDefinition* functionDefinition);
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
		private: void addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinition(NLCclassDefinition* functionDefinitionSource, NLCclassDefinition* functionDefinition);
		private: void addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinitionArguments(NLCclassDefinition* functionDefinitionSource, vector<NLCitem*>* functionDefinitionArgumentList);
	#endif
	#else
	//bool findFormalFunctionArgumentCorrelateInExistingList(NLCclassDefinition* functionClassDefinition, vector<NLCitem*>* formalFunctionArgumentList, vector<NLCclassDefinition*>* classDefinitionList);
	#endif
	#endif
#endif
	public: bool getFilesFromFileList(const string inputListFileName, vector<string>* inputTextFileNameList, int* numberOfInputFilesInList);
#endif
#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_ENTITY_NAMES_ONLY
	private: bool checkAlphaNumericEntityNames(vector<GIAentityNode*>* entityNodesActiveListComplete, const int maxNumberSentences);
#endif

	public: bool createFunctionDefinitionClassDefinition(vector<NLCclassDefinition*>* classDefinitionList, string NLCfunctionName, const int functionDefinitionIndex, const bool libraryFunctionDeclaration);
		public: NLCclassDefinition* createFunctionDefinitionClassDefinition(vector<NLCclassDefinition*>* classDefinitionList, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, const string functionClassDefinitionName, const string functionOwnerClassDefinitionName, const int functionDefinitionIndex, const bool isReferenceElseFunctionDefinition);
};


#endif
