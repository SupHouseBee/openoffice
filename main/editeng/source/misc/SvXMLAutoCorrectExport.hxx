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


#ifndef _SV_XMLAUTOCORRECTEXPORT_HXX
#define _SV_XMLAUTOCORRECTEXPORT_HXX

#include <xmloff/xmlictxt.hxx>
#include <xmloff/xmlexp.hxx>
#include <xmloff/nmspmap.hxx>
#include <xmloff/xmlnmspe.hxx>
#include <editeng/svxacorr.hxx>

class SvXMLAutoCorrectExport : public SvXMLExport
{
private:
	const SvxAutocorrWordList 	*pAutocorr_List;
public:
	// #110680#
	SvXMLAutoCorrectExport( 
		const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
		const SvxAutocorrWordList * pNewAutocorr_List, 
		const rtl::OUString &rFileName,
		com::sun::star::uno::Reference< com::sun::star::xml::sax::XDocumentHandler> &rHandler);

	virtual ~SvXMLAutoCorrectExport ( void ) {}
	sal_uInt32 exportDoc(enum ::xmloff::token::XMLTokenEnum eClass);
	void _ExportAutoStyles() {}
	void _ExportMasterStyles () {}
	void _ExportContent() {}
};

class SvStringsISortDtor;

class SvXMLExceptionListExport : public SvXMLExport
{
private:
	const SvStringsISortDtor & rList;
public:
	// #110680#
	SvXMLExceptionListExport( 
		const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
		const SvStringsISortDtor &rNewList, 
		const rtl::OUString &rFileName,
		com::sun::star::uno::Reference< com::sun::star::xml::sax::XDocumentHandler> &rHandler);

	virtual ~SvXMLExceptionListExport ( void ) {}
	sal_uInt32 exportDoc(enum ::xmloff::token::XMLTokenEnum eClass);
	void _ExportAutoStyles() {}
	void _ExportMasterStyles () {}
	void _ExportContent() {}
};
#endif
