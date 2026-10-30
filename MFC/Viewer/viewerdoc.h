#ifndef __VIEWERDOCUMENT_H
#define __VIEWERDOCUMENT_H

#include <model_entity.h>
#include <mb_scenegenerator.h>
#include <vsn_vision.h>

class MbModel;
/* ViewerDocument */
class ViewerDocument : public CDocument
{
protected: // create from serialization only
    ViewerDocument();
    DECLARE_DYNCREATE(ViewerDocument)

    // Attributes
public:
    SPtr<MbModel> GetModel() const { return m_pModel; }
    // Operations
public:

    // Overrides
public:
    virtual BOOL OnNewDocument();
    virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
    virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
    virtual void InitializeSearchContent();
    virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

    // Implementation
public:
    virtual ~ViewerDocument();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
protected:
    // Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()
#ifdef SHARED_HANDLERS
    // Helper function that sets search content for a Search Handler
    void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
private:
    SPtr<MbModel> m_pModel;
    SceneGenerator* m_pSceneGenerator;
};

#endif /* __VIEWERDOCUMENT_H */
