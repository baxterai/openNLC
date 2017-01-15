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
 * File Name: NLClibraryStandardSet.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q12b 22-August-2015
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#ifndef HEADER_NLC_LIBRARY_STANDARD_SET
#define HEADER_NLC_LIBRARY_STANDARD_SET

#include "../NLClibrary/NLClibraryGenericEntityClass.hpp"

#define NLC_USE_LIBRARY_SET_FUNCTION_ACTION_CONDITION_TO_NAME "to"

void setFunction(vector<NLCgenericEntityClass*>& setClassList, vector<NLCgenericEntityClass*>& setObjectClassList);

#endif
