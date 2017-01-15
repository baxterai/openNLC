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
 * File Name: NLCtranslatorCodeBlocksOperations.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u2d 26-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CODEBLOCKS_OPERATIONS
#define HEADER_NLC_TRANSLATOR_CODEBLOCKS_OPERATIONS

#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"
//#ifdef NLC_USE_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.h"	//required for
//#endif


bool generateCodeBlocksPart3subjectObjectConnections(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, int sentenceIndex, bool logicalConditionBooleanStatement, bool* logicalConditionBooleanStatementNegativeDetected);
	bool generateCodeBlocksPart3subjectObjectConnection(NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, GIAentityNode* entity, GIAentityNode* subjectEntity, GIAentityNode* objectEntity, GIAentityConnection* connection, bool foundSubject, bool foundObject, int connectionType, bool logicalConditionBooleanStatement, bool* logicalConditionBooleanStatementNegativeDetected);
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		bool generateObjectInitialisationsFunction(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* actionEntity, int sentenceIndex);
		#endif

bool generateContextBlocks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool generatedParentContext, string genericListAppendName);
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	bool generateContextBlocksCategories(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool generatedParentContext, string genericListAppendName);
	#endif
		bool generateContextBlocksSimple(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool generatedParentContext, string genericListAppendName);
			bool createCodeBlockForStatements(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* entity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables);
				bool createCodeBlockForConnectionType(int connectionType, NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* entity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables);
					bool sameReferenceSetReferencingConnectionCheck(GIAentityConnection* targetConnection, NLCgenerateContextBlocksVariables* generateContextBlocksVariables);
					bool createCodeBlockForGivenProperty(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* propertyEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject);
					bool createCodeBlockForGivenCondition(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* conditionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject);
					#ifdef NLC_RECORD_ACTION_HISTORY
					bool createCodeBlockForGivenAction(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* actionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject);
					bool createCodeBlockForGivenActionIncoming(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* actionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject);
					#endif
					#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_DEFINITIONS
					bool createCodeBlockForGivenDefinition(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* definitionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject);
					#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
					bool createCodeBlockForGivenAlias(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* definitionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject);
					#endif
					#endif
					#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
					bool hasConjunctionConditionConnection(GIAentityNode* conditionEntity, GIAentityNode* primaryEntityInLogicalConditionConjunctionSubset, int logicalConditionConjunctionIndex, GIAentityNode** foundLogicalConditionConjunction);
					#endif
					#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_OF_TARGET_AND_MULTIPLE_DEFINITE_ENTITIES
					string generateCandidateObjectName(GIAentityNode* objectEntity);
					#endif
		#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		bool createCodeBlockForStatementsForDefinitionChildren(NLCcodeblock** currentCodeBlockInTree, NLCcodeblock** lastCodeBlockInTree, GIAentityNode* parentInstance, GIAentityNode* parentConcept, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool generateContext, string genericListAppendName);
			bool addEntityToCategoryList(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, string genericListAppendName, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, int sentenceIndex, bool castToCategoryType);
		#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_SUBCLASSES
		bool findNearestSubClassParentEntityCorrespondingToSubclassEntityInSameContext(GIAentityNode* subclassEntity, GIAentityNode** nearestSubclassParentEntity);
			bool entityHasPropertyParent(GIAentityNode* entity, string propertyParentName);
			bool createCodeBlockForStatementsForNearestSubClassParentReference(NLCcodeblock** currentCodeBlockInTree, NLCcodeblock** lastCodeBlockInTree, GIAentityNode* subclassEntity, GIAentityNode* nearestSubclassParentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool generateContext, string genericListAppendName);
		#endif
		#endif

bool getParentAndInitialiseParentIfNecessary(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool parseLogicalConditions, GIAentityNode** parentEntity, bool* newInitialisation);
bool getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool parseLogicalConditions, GIAentityNode** parentEntity, bool* newInitialisation);
bool generateParentInitialisationCodeBlockWithChecks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, bool parseLogicalConditions, bool testOnly);
	bool generateObjectInitialisations(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex);
		bool generateObjectInitialisationsForConnectionType(NLCcodeblock** currentCodeBlockInTree, int connectionType, GIAentityNode* entity, int sentenceIndex);
			bool generateCodeBlocksAddConnection(NLCcodeblock** currentCodeBlockInTree, int connectionType, GIAentityConnection* connection, GIAentityNode* subjectEntity, GIAentityNode* objectEntity, GIAentityNode* actionOrConditionEntity, bool foundSubject, bool foundObject, int sentenceIndex, GIAentityNode* subjectParentEntity, bool primary);
				#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
				bool isNonImmediateAction(GIAentityNode* actionEntity);
				bool isPotentialAction(GIAentityNode* actionEntity);
				#endif
			#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
			bool generateCodeBlocksVerifyConnection(NLCcodeblock** currentCodeBlockInTree, int connectionType, GIAentityConnection* connection, GIAentityNode* subjectEntity, GIAentityNode* objectEntity, GIAentityNode* actionOrConditionEntity, bool foundSubject, bool foundObject, int sentenceIndex, GIAentityNode* subjectParentEntity, bool primary, bool* logicalConditionBooleanStatementNegativeDetected);
			#endif
			bool getActionSubjectCheckSameReferenceSetAndSentence(GIAentityNode* actionEntity, GIAentityNode** subjectEntity, GIAentityConnection** actionSubjectConnection, int sentenceIndex, bool sameReferenceSet);
				bool getActionSubjectEntityConnection(GIAentityNode* actionEntity, int sentenceIndex, GIAentityConnection** actionSubjectConnection);
			bool getActionObjectCheckSameReferenceSetAndSentence(GIAentityNode* actionEntity, GIAentityNode** objectEntity, GIAentityConnection** actionObjectConnection, int sentenceIndex, bool sameReferenceSet);
				bool getActionObjectEntityConnection(GIAentityNode* actionEntity, int sentenceIndex, GIAentityConnection** actionObjectConnection);
			bool getConditionSubjectCheckSameReferenceSetAndSentence(GIAentityNode* conditionEntity, GIAentityNode** subjectEntity, GIAentityConnection** conditionSubjectConnection, int sentenceIndex, bool sameReferenceSet);
				bool getConditionSubjectEntityConnection(GIAentityNode* conditionEntity, int sentenceIndex, GIAentityConnection** conditionSubjectConnection);
			bool getConditionObjectCheckSameReferenceSetAndSentence(GIAentityNode* conditionEntity, GIAentityNode** objectEntity, GIAentityConnection** conditionObjectConnection, int sentenceIndex, bool sameReferenceSet);
				bool getConditionObjectEntityConnection(GIAentityNode* conditionEntity, int sentenceIndex, GIAentityConnection** conditionObjectConnection);

GIAentityNode* getParent(GIAentityNode* currentEntity, int sentenceIndex);
	GIAentityNode* getParent(GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables);
bool getParentAndGenerateContextBlocks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables);

bool generateContextForChildEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* childEntity, int sentenceIndex, bool topLevel, bool logicalConditionBooleanStatement);
	bool generateContextBlocksForParentEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* childEntity, GIAentityNode* parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables);
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
	GIAentityNode* getSameReferenceSetUniqueParent(GIAentityNode* currentEntity, int sentenceIndex, GIAentityNode* generateObjectInitialisationsLastParent, bool* foundParentEntityNew, bool parseConditionParents, bool checkIsDefinite);
	#endif
GIAentityNode* getSameReferenceSetSubstanceNonQualityChild(GIAentityNode* parentEntity, int sentenceIndex, bool *foundChildEntity);

#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
void generateObjectInitialisationsBasedOnConcepts(GIAentityNode* targetEntity, GIAentityNode* entity, NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, bool newlyDeclaredEntityInCategoryList);
	void generateObjectInitialisationsBasedOnConceptsRecurse(GIAentityNode* targetEntity, GIAentityNode* definitionEntity, NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, GIAentityNode* parentEntity, string parentConditionName, bool newlyDeclaredEntityInCategoryList);
#endif

#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
void fillFunctionAliasClassList(vector<GIAentityNode*>* entityNodesActiveListComplete);
#endif

bool checkSpecialCaseEntity(GIAentityNode* entity, bool detectActions);
bool checkNetworkIndexTypeEntity(GIAentityNode* entity);

#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
bool generateContextBasedOnDeclaredParent(GIAentityNode* entity, NLCcodeblock** currentCodeBlockInTree, bool topLevel, GIAentityNode* generateObjectInitialisationsLastParent, int sentenceIndex, bool logicalConditionBooleanStatement);
#endif

#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT_ORIGINAL_IMPLEMENTATION
void addIntermediaryImplicitlyDeclaredEntityToLocalList(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* childEntity, int sentenceIndex);
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
bool checkConditionLogicalConditionAdvancedTests(GIAentityNode* conditionEntity);
#endif

#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
bool checkNumerosity(GIAentityNode* entity);
#endif

bool generateObjectInitialisationsAction(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* actionEntity, int sentenceIndex);

bool checkParentExists(GIAentityNode* object, string parentName);

#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
void secondaryComparisonSetIDinstance(GIAentityNode* entity);
void secondaryComparisonRestoreIDinstance(GIAentityNode* entity);
#endif

#endif
