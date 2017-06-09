/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is licensed under the GNU Affero General Public License
 * version 3, as published by the Free Software Foundation. The use of
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
 * File Name: NLCmain.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2c1e 01-June-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_MAIN
#define HEADER_NLC_MAIN

#include "NLCglobalDefs.hpp"
#include "NLCcodeBlockClass.hpp"
#include "NLCclassDefinitionClass.hpp"
#include "NLCtranslator.hpp"
#include "NLCprint.hpp"
#include "NLCprintClassDefinitions.hpp"
#include "NLCprintCodeBlocks.hpp"
#include "NLCpreprocessor.hpp"
#include "NLCtranslatorClassDefinitions.hpp"
#include "NLCprintDefs.hpp"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, setProgLang
#ifdef NLC_API
#include "NLCapi.hpp"
#endif
#include "NLCtranslatorCodeBlocksOperations.hpp"
#include "GIAmain.hpp"
#include "GIAdatabase.hpp"
#ifdef USE_WORDNET
#include "GIAwordnet.hpp"
#endif
#ifdef GIA_SEMANTIC_PARSER
#include "GIAsemanticParserDatabase.hpp"
#endif
#include "GIAtranslatorOperations.hpp"
#include "GIAtranslatorDefs.hpp"
#include "XMLrulesClass.hpp"
#include "SHAREDvars.hpp"

int main(const int argc, const char** argv);

class NLCmainClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: GIAentityNodeClassClass GIAentityNodeClass;
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	private: NLCclassDefinitionClassClass NLCclassDefinitionClass;
	private: NLCtranslatorClass NLCtranslator;
	private: NLCtranslatorClassDefinitionsClass NLCtranslatorClassDefinitions;
	private: NLCcodeBlockClassClass NLCcodeBlockClass;
		private: string removeFileNameExtensions(string NLCfunctionName);
		#ifdef NLC_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED
		public: string removeNLCfileNameExtension(string NLCfunctionName);
		#endif
		#ifdef NLC_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY
		public: void transformTheActionOfPossessionEgHavingIntoAproperty(vector<GIAentityNode*>* entityNodesActiveListComplete);
		#endif
		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
		public: bool generateClassDefinitionFunctionDeclarationsAndReconcileArguments(const int numberOfInputFilesInList, vector<NLCclassDefinition*>* classDefinitionList, vector<vector<GIAentityNode*>*>* entityNodesActiveListCompleteFunctions, vector<NLCcodeblock*>* firstCodeBlockInTreeList);
		#endif
		#ifndef NLC_LIBRARY
		private: void printPredefinedNLCfunctions(NLCcodeblock* currentCodeBlockInTree);
		#endif
		
	public: bool executeNLC(

		NLCfunction* firstNLCfunctionInList,
		GIAtranslatorVariablesClass* translatorVariablesTemplate,
		
		string inputFolderLocal, 
		string outputFolderLocal,
		string NLPexeFolderArray[],

		bool useInputTextPlainTXTFile,
		string inputTextPlainTXTfileName,
		#ifdef NLC_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE
		bool useNLCinputFileList,
		string NLCinputFileListName,
		#endif
	
		string outputTextNLPrelationXMLfileName,
		string outputTextNLPfeatureXMLfileName,
		bool useOutputTextCFFFile,
		string outputTextCFFFileName,
		bool useOutputTextXMLFile,
		string outputTextXMLFileName,
		bool useOutputTextCXLFile,
		string outputTextCXLFileName,
		bool useOutputTextLDRFile,
		string outputTextLDRFileName,
		bool useOutputTextPPMFile,
		string outputTextPPMFileName,
		bool useOutputTextSVGFile,
		string outputTextSVGFileName,

		bool useOutputTextAllFile,
		string outputTextAllFileName,

		//#ifdef NLC_PREPROCESSOR
		bool useNLCpreprocessor,
		//#endif
		#ifdef NLC_API
		bool NLCapi,
		string APIsourceFolder,
		string APIclassListFileName,
		#endif
		bool printOutput,
		bool displayInOpenGLAndOutputScreenshot,

		int rasterImageWidth,
		int rasterImageHeight,

		#ifdef GIA_DATABASE
		bool readFromDatabase,
		bool writeToDatabase,
		bool useDatabase,
		string databaseFolderName,
		#endif
		#ifdef GIA_SEMANTIC_PARSER
		string semanticParserDatabaseFolderName,
		#endif

		#ifdef GIA_PREPROCESSOR
		bool useLRP,
		bool useOutputLRPTextPlainTXTFile,
		string outputLRPTextPlainTXTFileName,
		string lrpDataFolderName,
		#endif

		#ifdef USE_WORDNET
		int synonymnDetectionStatus
		#endif
		);
	
	#ifdef USE_CS_WORKAROUND
	bool GIAmainClass::executeNLC2();
	#endif
};
	


#endif
