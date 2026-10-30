// MFCApplication1Doc.cpp : implementation of the ViewerDocument class
#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "viewerapplication.h"
#endif

#include <io_tape.h>
#include <io_memory_buffer.h>
#include <propkey.h>
#include <model.h>
#include <conv_model_exchange.h>
#include <conv_exchange_settings.h>

#include "viewerdoc.h"
#include "viewerview.h"
#include <vsn_last.h>


// ViewerDocument
IMPLEMENT_DYNCREATE(ViewerDocument, CDocument)

BEGIN_MESSAGE_MAP(ViewerDocument, CDocument)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
//
// ----
ViewerDocument::ViewerDocument()
    : m_pModel(new MbModel)
    , m_pSceneGenerator(new SceneGenerator())
{
}

//-----------------------------------------------------------------------------
//
// ----
ViewerDocument::~ViewerDocument()
{
    VSN_DELETE_AND_NULL(m_pSceneGenerator);
}

//-----------------------------------------------------------------------------
//
// ----
BOOL ViewerDocument::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;
    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)
    return TRUE;
}

//-----------------------------------------------------------------------------
// user has opened a file
// ---
BOOL ViewerDocument::OnOpenDocument(LPCTSTR lpszPathName)
{
    MbModel model;
    ConvConvertorProperty3D convProperties;
    convProperties.enableAutostitch = true;
    convProperties.autostitchPrecision = Math::visualSag;
    convProperties.fileName = lpszPathName;

    if ( c3d::ImportFromFile( model, lpszPathName, &convProperties, nullptr ) == cnv_Success ) {
        m_pModel.reset();
        m_pModel = SPtr<MbModel>( new MbModel() );
        for ( MbModel::ItemIterator iter = model.Begin(), last = model.End(); iter != last; ++iter )
            m_pModel->AddItem( *( *iter ) );
        for ( POSITION posView = GetFirstViewPosition(); posView != NULL;) {
            CView * pView = GetNextView( posView );
            ASSERT_VALID( pView );
            ViewerView * pOpenGLView = dynamic_cast< ViewerView * >( pView );
            ASSERT_VALID( pOpenGLView );
            pOpenGLView->UpdateSceneForModel( m_pModel );
            break;
        }
        return TRUE;
    }
    return FALSE;
}

//-----------------------------------------------------------------------------
// serialization
// ----
void ViewerDocument::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // TODO: add storing code here
    }
    else
    {
        // TODO: add loading code here
    }
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void ViewerDocument::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
    // Modify this code to draw the document's data
    dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

    CString strText = _T("TODO: implement thumbnail drawing here");
    LOGFONT lf;

    CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
    pDefaultGUIFont->GetLogFont(&lf);
    lf.lfHeight = 36;

    CFont fontDraw;
    fontDraw.CreateFontIndirect(&lf);

    CFont* pOldFont = dc.SelectObject(&fontDraw);
    dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
    dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void ViewerDocument::InitializeSearchContent()
{
    CString strSearchContent;
    // Set search contents from document's data. 
    // The content parts should be separated by ";"

    // For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
    SetSearchContent(strSearchContent);
}

void ViewerDocument::SetSearchContent(const CString& value)
{
    if (value.IsEmpty())
    {
        RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
    }
    else
    {
        CMFCFilterChunkValueImpl *pChunk = NULL;
        ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
        if (pChunk != NULL)
        {
            pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
            SetChunkValue(pChunk);
        }
    }
}

#endif // SHARED_HANDLERS

// ViewerDocument diagnostics

#ifdef _DEBUG
void ViewerDocument::AssertValid() const
{
    CDocument::AssertValid();
}

void ViewerDocument::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// ViewerDocument commands
