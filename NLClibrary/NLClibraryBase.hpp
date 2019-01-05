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
 * File Name: NLClibraryBase.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2f11a 20-April-2018
 * Requirements: requires C++ code to be generated by NLC
 * Description: Base NLC library Functions (no generic property and condition lists) 
 * Note: These functions are hard coded
 *
 *******************************************************************************/
 
#ifndef HEADER_NLC_LIBRARY_BASE
#define HEADER_NLC_LIBRARY_BASE

#include "NLClibraryGenericEntityClass.hpp"
#ifdef NLC_LIBRARY_BASE_EXTENDED
#include "NLClibraryBaseExtended.hpp"
#endif

#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
template <class E1, class E2>
void addToCategoryIfPassPluralDefiniteReferencingTests(vector<E1*>& entityCategoryList, E2* entity0);
#endif
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
template <class E1, class E2>
vector<E2*>& castVector(vector<E1*>& E1List);
#ifdef NLC_CONDITION_LISTS_VECTOR
template <class E1, class E2, class E3, class E4>
vector<pair<E3*, E4*>*>& castVectorPair(vector<pair<E1*, E2*>*>& E1E2List);
#else
template <class E1, class E2, class E3, class E4>
unordered_map<E3*, E4*>& castUnorderedMap(unordered_map<E1*, E2*>& E1E2List);	//not currently used
#endif
#endif

#ifdef NLC_ADVANCED_REFERENCING
#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
template <class E1, class E2>
void addToCategoryIfPassSingularDefiniteReferencingTests(vector<E1*>& entityCategoryList, E2* entity0);
#endif
#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
template <class E1>
void findAliasAndAddToCategoryList(vector<E1*>& E1List, string aliasName, vector<E1*>& E1CategoryList);
template <class E1>
bool findAliasNewFunction(E1* E1instance, string aliasName);
#endif
#endif

#include "NLClibraryBase.cpp"

#endif
