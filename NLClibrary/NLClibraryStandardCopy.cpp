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
 * File Name: NLClibraryStandardCopy.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1p3f 25-June-2015
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryStandardCopy.h"
#include "NLClibraryStandardOperations.h"

//UNFINISHED 
//e.g. Copy the chicken [from the pie] to the apple.
void copyFunction(vector<copyClass*> &copyClassList, vector<NLCgenericEntityClass*> &copyObjectClassList)
{
	for(vector<NLCgenericEntityClass*> ::iterator iter1 = copyClassList.begin(); iter1 < copyClassList.end(); iter1++) 
	{
		copyAction = *iter2;
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityFromConditionList = getConditionListByConditionName(copyAction, NLC_USE_LIBRARY_MOVE_FUNCTION_ACTION_CONDITION_FROM_NAME); 
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityToConditionList = getConditionListByConditionName(copyAction, NLC_USE_LIBRARY_MOVE_FUNCTION_ACTION_CONDITION_TO_NAME); 

		if(NLCgenericEntityFromConditionList != NULL)
		{
			if(NLCgenericEntityToConditionList != NULL)	//this will fail with Stanford NLP until * has been implemented
			{
				for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> ::iterator iter2 = NLCgenericEntityFromConditionList.begin(); iter2 != NLCgenericEntityFromConditionList.end(); iter2++)
				{
					NLCgenericEntityClass* fromConditionObject = iter2->second;
					for(vector<NLCgenericEntityClass*> ::iterator iter3 = copyObjectClassList.begin(); iter3 < copyObjectClassList.end(); iter3++) 
					{
						NLCgenericEntityClass* copyObject = *iter3;
						bool copyObjectFoundAttachedAsPropertyAndHasBeenRecopyd = false;
						vector<NLCgenericEntityClass*>* fromObjectCopyObjectPropertyList = getPropertyListByName(fromConditionObject, copyObject->name); 
						if(fromObjectCopyObjectPropertyList != NULL)
						{
							if(recopyItemFromVectorList(fromObjectCopyObjectPropertyList, copyObject))	//this should now work with GIA_DYNAMICALLY_LINK_FROM_CONDITIONS:linkEntitiesDynamicFromConditions
							{	
								copyObjectFoundAttachedAsPropertyAndHasBeenRecopyd = true;
							}
						}

						if(copyObjectFoundAttachedAsPropertyAndHasBeenRecopyd)
						{
							for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> ::iterator iter4 = NLCgenericEntityToConditionList.begin(); iter4 != NLCgenericEntityToConditionList.end(); iter4++)
							{
								NLCgenericEntityClass* toConditionObject = iter4->second;
  								addPropertyGeneric(toConditionObject, copyObject);
								#ifdef NLC_DEBUG_LIBRARY
								cout << "copy() pass: copyParentOld (fromConditionObject) = " << fromConditionObject->name << ", copyObject = " << copyObject->name << "copyParentNew (toConditionObject) = " << toConditionObject->name << endl;
								#endif
							}
						}
						else
						{
							cout << "copy() error: copy object parent not found" << endl;
						}
					}
				}
			}
			else
			{
				cout << "copy() error: copy action 'from' condition not found" << endl;
			}
		}
		else
		{
			cout << "copy() error: copy action 'to' condition not found" << endl;
		}
	}
}

