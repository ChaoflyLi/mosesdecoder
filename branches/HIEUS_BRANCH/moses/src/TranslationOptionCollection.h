// $Id$

/***********************************************************************
Moses - factored phrase-based language decoder
Copyright (C) 2006 University of Edinburgh

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
***********************************************************************/

#pragma once

#include <list>
#include "TypeDef.h"
#include "TranslationOption.h"
#include "SquareMatrix.h"
#include "WordsBitmap.h"
#include "PartialTranslOpt.h"
#include "PartialTranslOptColl.h"

class Sentence;
class DecodeStep;
class LanguageModel;
class FactorCollection;


class TranslationOptionCollection : public std::list< TranslationOption >
{
protected:
	const Sentence &m_inputSentence;
	SquareMatrix m_futureScore;
	WordsBitmap m_initialCoverage;

	void ProcessInitialTranslation(const DecodeStep &decodeStep
															, const LMList &languageModels
															, const LMList &allLM
															, FactorCollection &factorCollection
															, float weightWordPenalty
															, int dropUnknown
															, size_t verboseLevel
															, PartialTranslOptColl &outputPartialTranslOptColl);
	void ProcessUnknownWords();
	void ProcessTranslation(		const PartialTranslOpt &inputPartialTranslOpt
															, const DecodeStep &decodeStep
															, PartialTranslOptColl &outputPartialTranslOptColl);
	void ProcessGeneration(			const PartialTranslOpt &inputPartialTranslOpt
															, const DecodeStep &decodeStep
															, PartialTranslOptColl &outputPartialTranslOptColl);

public:
	TranslationOptionCollection(const Sentence &inputSentence);

		inline const SquareMatrix &GetFutureScore()
	{
		return m_futureScore;
	}
	inline const WordsBitmap &GetInitialCoverage() const 
	{
		return m_initialCoverage;
	}

  void CreateTranslationOptions(const std::list < DecodeStep > &decodeStepList
  														, const LMList &languageModels  														
  														, const LMList &allLM
  														, FactorCollection &factorCollection
  														, float weightWordPenalty
  														, int dropUnknown
  														, size_t verboseLevel);
};

inline std::ostream& operator<<(std::ostream& out, const TranslationOptionCollection& coll)
{
	TranslationOptionCollection::const_iterator iter;
	for (iter = coll.begin() ; iter != coll.end() ; ++iter)
	{
		TRACE_ERR (*iter << std::endl);
	}	
	return out;
};

