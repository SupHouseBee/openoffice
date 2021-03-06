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



#ifndef _SVEDIT_HXX
#define _SVEDIT_HXX

#include <tools/wintypes.hxx>
#include <vcl/edit.hxx>

#include <svtools/syntaxhighlight.hxx>
#include <svtools/svtdllapi.h>
#include <svtools/colorcfg.hxx>

class ImpSvMEdit;
class Timer;
class ExtTextEngine;
class ExtTextView;

class SVT_DLLPUBLIC MultiLineEdit : public Edit
{
private:
	ImpSvMEdit*		pImpSvMEdit;

	XubString		aSaveValue;
	Link			aModifyHdlLink;

	Timer*			pUpdateDataTimer;
	Link			aUpdateDataHdlLink;

protected:

	DECL_LINK( 		ImpUpdateDataHdl, Timer* );
	void 			StateChanged( StateChangedType nType );
	void 			DataChanged( const DataChangedEvent& rDCEvt );
	virtual long 	PreNotify( NotifyEvent& rNEvt );
	long 			Notify( NotifyEvent& rNEvt );
    using Control::ImplInitSettings;
	void 			ImplInitSettings( sal_Bool bFont, sal_Bool bForeground, sal_Bool bBackground );
	WinBits 		ImplInitStyle( WinBits nStyle );

	ExtTextEngine*	GetTextEngine() const;
	ExtTextView*	GetTextView() const;
	ScrollBar*		GetHScrollBar() const;
	ScrollBar*		GetVScrollBar() const;

public:
					MultiLineEdit( Window* pParent, WinBits nWinStyle = WB_LEFT | WB_BORDER );
					MultiLineEdit( Window* pParent, const ResId& rResId );
					~MultiLineEdit();


	virtual void	Modify();
	virtual void	UpdateData();

	virtual void	SetModifyFlag();
	virtual void	ClearModifyFlag();
	virtual sal_Bool	IsModified() const;

	virtual void	EnableUpdateData( sal_uLong nTimeout = EDIT_UPDATEDATA_TIMEOUT );
	virtual void	DisableUpdateData() { delete pUpdateDataTimer; pUpdateDataTimer = NULL; }
	virtual sal_uLong	IsUpdateDataEnabled() const;

	virtual void	SetReadOnly( sal_Bool bReadOnly = sal_True );
	virtual sal_Bool	IsReadOnly() const;

	void			EnableFocusSelectionHide( sal_Bool bHide );
	sal_Bool			IsFocusSelectionHideEnabled() const;

	virtual void	SetMaxTextLen( xub_StrLen nMaxLen = 0 );
	virtual xub_StrLen GetMaxTextLen() const;

	virtual void	SetSelection( const Selection& rSelection );
	virtual const Selection& GetSelection() const;

	virtual void	    ReplaceSelected( const XubString& rStr );
	virtual void	    DeleteSelected();
	virtual XubString	GetSelected() const;
	virtual XubString	GetSelected( LineEnd aSeparator ) const;

	virtual void	Cut();
	virtual void	Copy();
	virtual void	Paste();

	virtual void    SetText( const XubString& rStr );
	virtual void    SetText( const XubString& rStr, const Selection& rNewSelection )
                    { SetText( rStr ); SetSelection( rNewSelection ); }
	String			GetText() const;
	String			GetText( LineEnd aSeparator ) const;
	String			GetTextLines() const;
	String			GetTextLines( LineEnd aSeparator ) const;

    void            SetRightToLeft( sal_Bool bRightToLeft );
    sal_Bool            IsRightToLeft() const;

	void			SaveValue() 						{ aSaveValue = GetText(); }
	const XubString&	GetSavedValue() const 				{ return aSaveValue; }

	void			SetModifyHdl( const Link& rLink ) 	{ aModifyHdlLink = rLink; }
	const Link&		GetModifyHdl() const 				{ return aModifyHdlLink; }

	void			SetUpdateDataHdl( const Link& rLink ) { aUpdateDataHdlLink = rLink; }
	const Link&		GetUpdateDataHdl() const { return aUpdateDataHdlLink; }

	virtual void	Resize();
	virtual void	GetFocus();

	Size			CalcMinimumSize() const;
	Size			CalcAdjustedSize( const Size& rPrefSize ) const;
    using Edit::CalcSize;
	Size			CalcSize( sal_uInt16 nColumns, sal_uInt16 nLines ) const;
	void			GetMaxVisColumnsAndLines( sal_uInt16& rnCols, sal_uInt16& rnLines ) const;

	void 			Draw( OutputDevice* pDev, const Point& rPos, const Size& rSize, sal_uLong nFlags );

   	void			SetLeftMargin( sal_uInt16 n );
	sal_uInt16			GetLeftMargin() const;

    virtual
    ::com::sun::star::uno::Reference< ::com::sun::star::awt::XWindowPeer >
    GetComponentInterface(sal_Bool bCreate = sal_True);

    void            DisableSelectionOnFocus();
};

inline sal_uLong MultiLineEdit::IsUpdateDataEnabled() const
{
	return pUpdateDataTimer ? pUpdateDataTimer->GetTimeout() : 0;
}

#endif
