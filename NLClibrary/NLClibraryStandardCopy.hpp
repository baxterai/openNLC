/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is commercially licensed software. It may not be redistributed,
 * and may only be used by a registered licensee.
 *
 * BAIPROJECT is sold in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * BAI Commercial License for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You will have received a copy of the BAI Commercial License
 * along with BAIPROJECT. For more information, visit <http://www.baxterai.com>
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryStandardCopy.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u7a 28-September-2016
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/

#ifndef HEADER_NLC_LIBRARY_STANDARD_COPY
#define HEADER_NLC_LIBRARY_STANDARD_COPY

#include "NLClibraryGenericEntityClass.hpp"

void copyFunction(vector<NLCgenericEntityClass*>& copyClassList, vector<NLCgenericEntityClass*>& copyObjectClassList);
NLCgenericEntityClass* copyObjectAndChildren(NLCgenericEntityClass* objectToCopy);
	NLCgenericEntityClass* copyObjectAndProperties(NLCgenericEntityClass* objectToCopy);
	#ifdef NLC_USE_LIBRARY_COPY_FUNCTION_COPY_INTERNAL_CONDITION_LISTS
	void copyConditionLinks(NLCgenericEntityClass* objectToCopyTopLevel, NLCgenericEntityClass* objectToCopy, NLCgenericEntityClass* copyOfCopyObject);
		bool findObjectInPropertyHierarchy(NLCgenericEntityClass* object, NLCgenericEntityClass* objectToFind);
	#endif
NLCgenericEntityClass* copyObjectByNameWithoutChildren(string name, NLCgenericEntityClass* entityToCopy);
#endif
