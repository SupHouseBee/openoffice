/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#ifndef _SV_SALFONT_H
#define _SV_SALFONT_H

// -=-= exports =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class	SalFontCache;
struct	SalFontDimension;
class	SalFontFamily;
class	SalFontFamilyList;
class	SalFontStruct;
class	SalFontStructList;
class	SalFonts;

// -=-= includes -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <salstd.hxx>
#include <vcl/outfont.hxx>

// -=-= forwards =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
typedef ULONG XFP_FLAGS;

class	SalDisplay;
class	SalFontCacheItem;

// -=-= SalFontCache -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
DECLARE_LIST( SalFontCache, SalFontCacheItem* )

// -=-= SalFontDimension -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
struct SalFontDimension
{
			USHORT		nHeight_;				// [pixel]
			USHORT		nPtHeight_;				// [point/10]
			USHORT		nAverage_;				// [pixel/10]
			USHORT		nXRes_;					// [dpi]
			USHORT		nYRes_;					// [dpi]
			USHORT      nSlant_;				// [pixel]
//			size_t		nUnderlineThickness_;	// [pixel]
//			size_t      nUnderlinePosition_;    // [pixel]
//			size_t      nStrikeoutAscent_;      // [pixel]
//			size_t      nStrikeoutDescent_;     // [pixel]
//			Subscript, Superscript, Capital, Space ...

	inline				SalFontDimension( USHORT nA = 0, USHORT nH = 0 );

	inline	BOOL		IsScalable() const;
	inline	USHORT		GetWidth() const { return (nAverage_ + 5) / 10; }
	inline	Size		GetSize() const;
	inline	void		SetSize( const Size & rSize );
	inline	BOOL		operator == ( const SalFontDimension &r ) const;
	inline	BOOL		operator != ( const SalFontDimension &r ) const;
	inline	BOOL		operator >= ( const SalFontDimension &r ) const;
};

inline SalFontDimension::SalFontDimension( USHORT nA, USHORT nH )
	: nHeight_( nH ), nAverage_( nA )
{ nPtHeight_ = nXRes_ = nYRes_ = nSlant_ = 0; }

inline BOOL	SalFontDimension::IsScalable() const
{ return !nHeight_ && !nPtHeight_ && !nAverage_; }

inline Size	SalFontDimension::GetSize() const
{ return Size( (nAverage_ + 5) / 10, nHeight_ ); }

inline void	SalFontDimension::SetSize( const Size & rSize )
{ nAverage_ = (USHORT)rSize.Width() * 10; nHeight_ = (USHORT)rSize.Height(); }

inline BOOL	SalFontDimension::operator == ( const SalFontDimension &r ) const
{ return nHeight_ == r.nHeight_ && (!r.nAverage_ || nAverage_ == r.nAverage_); }

inline BOOL	SalFontDimension::operator != ( const SalFontDimension &r ) const
{ return !(*this == r); }

inline BOOL	SalFontDimension::operator >= ( const SalFontDimension &r ) const
{ return nHeight_ > r.nHeight_
		 || (nHeight_ == r.nHeight_ && nAverage_ >= r.nAverage_); }

// -=-= SalFontStruct =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class SalFontStruct : public ImplFontMetricData
{
	friend class SalDisplay;
	friend class SalGraphicsData;

			SalFontCacheItem*pCache_;

#if (OSL_DEBUG_LEVEL > 1) || defined  DBG_UTIL
			ByteString		aFontName_;
#endif
			USHORT			nHeightCount_;		// Anzahl der Hoehen-Eintraege
			SalFontDimension*pDimensions_;		// Hoehen-Array
			USHORT			nWeight_;

			USHORT			nFoundry_;			// properties indexies
			USHORT			nFamily_;
			USHORT			nWeightName_;
			USHORT			nSlant_;
			USHORT			nSetWidthName_;
			ByteString		aAddStyleName_;
			USHORT			nSpacing_;
			USHORT			nCharSet_;
			USHORT			nFaceName_;
			BOOL            mbValidFontDescription;	// valid xlfd entries

			void			Init();
			BOOL			Init( SalDisplay*		pDisp,
								  const char*		pFontName,
								  SalFontDimension&	rDim );

			ByteString		GetXFontName( const SalFontDimension& );

	inline	void			SetFoundry( USHORT n )
		{ nFoundry_ = n; }
	inline	void			SetFamily( USHORT n )
		{ meFamily = sal_FamilyToSal( nFamily_ = n ); }
	inline	void			SetWeightName( USHORT n )
		{ meWeight = sal_WeightToSal( nWeightName_ = n ); }
	inline	void			SetSlant( USHORT n )
		{ meItalic = sal_ItalicToSal( nSlant_ = n ); }
	inline	void			SetSetWidthName( USHORT n )
		{ nSetWidthName_ = n; }
	inline	void			SetAddStyleName( const ByteString& rAddStyle )
		{ aAddStyleName_ = rAddStyle; aAddStyleName_.ToLowerAscii(); }
	inline	void			SetSpacing( USHORT n )
		{ mePitch = sal_PitchToSal( nSpacing_ = n ); }
	inline	void			SetAverage( long n )
		{ mnWidth = (n + 5) / 10; }
	void					SetCharSet( USHORT n );

							SalFontStruct( const SalFontStruct& rFont );
public:
							SalFontStruct( SalDisplay*			pDisp,
										   const char*			pFontName,
										   SalFontDimension&	rDim );

							~SalFontStruct();

	inline	void			Cache( SalFontCacheItem *p ) { pCache_ = p; }
	inline	SalFontCacheItem*IsCache() const { return pCache_; }
	inline	BOOL			IsScalable() const { return TYPE_SCALABLE==meType; }
	inline	SalFontDimension*GetDim() const { return pDimensions_; }
	inline  BOOL			IsValid() const { return mbValidFontDescription; }
#ifdef DBG_UTIL
        	const ByteString&	GetName() const { return aFontName_; }
#endif

			ImplFontData   *GetDevFontData();
			SalFontCacheItem*Load( SalDisplay *pDisp, const SalFontDimension &rDim );
			CharSet GetCharSet() { return meCharSet; }

};

// -=-= SalFontStructList =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
DECLARE_LIST( SalFontStructList, SalFontStruct* )

#endif // _SV_SALFONT_H

