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
 * File Name: NLClibraryStandardAdd.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1r5c 15-August-2016
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryStandardAdd.hpp"
#include "NLClibraryStandardOperations.hpp"
#include "NLCgenerated.hpp"

//e.g. "Add the apple to the tree." / "Add the reference to the item's forwardReferenceClassList."
void addFunction(vector<NLCgenericEntityClass*>& addClassList, vector<NLCgenericEntityClass*>& addObjectClassList)
{
	for(vector<NLCgenericEntityClass*>::iterator iter1 = addClassList.begin(); iter1 < addClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* addAction = *iter1;

		for(vector<NLCgenericEntityClass*>::iterator iter2 = addObjectClassList.begin(); iter2 < addObjectClassList.end(); iter2++) 
		{
			NLCgenericEntityClass* addObject = *iter2;
			
			//see redistributeStanfordRelationsConnectToAndFromConditions{} for necessary preprocessing of to conditions
			unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityToConditionList = getConditionListByConditionName(addAction, NLC_USE_LIBRARY_FUNCTION_ACTION_CONDITION_TO_NAME); 

			if(NLCgenericEntityToConditionList != NULL)
			{	
				//eg "Add the apple to the tree." / "Add the reference to the item's forwardReferenceClassList."
				for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter3 = NLCgenericEntityToConditionList->begin(); iter3 != NLCgenericEntityToConditionList->end(); iter3++)
				{
					NLCgenericEntityClass* toConditionObject = iter3->second;
					addPropertyGeneric(toConditionObject, addObject);
				}
			}
		}
	}
}




