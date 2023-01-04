// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/splitter.h>
#include <wx/textfile.h>
#include <wx/string.h>
#include <stdio.h>
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};


class MyFrame : public wxFrame
{
public:
    MyFrame();
    wxTextCtrl text;
    wxTextFile tfile;
    wxTextCtrl viewfile;
//event table
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void SearchText(wxCommandEvent& event);
    void FileSearch(wxCommandEvent& event);
    void OnFileNameClick(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};


wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_BUTTON(1, MyFrame::FileSearch) //search for files
EVT_BUTTON(2, MyFrame::SearchText) //search text in file
EVT_BUTTON(3, MyFrame::OnFileNameClick)
EVT_TEXT(wxID_ANY, MyFrame::OnHello)//test
wxEND_EVENT_TABLE()

enum
{
    ID_Hello = 1

};

wxIMPLEMENT_APP(MyApp);

//create new wxFrame when MyApp is initialized
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

//CODE LOOP
MyFrame::MyFrame(): wxFrame(nullptr, wxID_ANY, "TestApp",wxDefaultPosition, wxSize(1200, 840
))
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");


    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText("Status Bar");

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);


    //LEFT SPLITTER
    wxSplitterWindow *leftsplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxSize(400, 840), wxSP_LIVE_UPDATE | wxSP_VERTICAL| wxSP_BORDER);
    //File splitter and pane
    wxPanel *Files = new wxPanel(leftsplitter, wxID_ANY, wxPoint(0,0), wxDefaultSize);
    //left panel button sizer
    wxBoxSizer *leftsizer = new wxBoxSizer(wxVERTICAL);
    //Folder Search
    wxButton *button = new wxButton(Files, 1, _T("Open Folder"), wxPoint(50, 565), wxSize(100,20), wxSP_THIN_SASH);
    //File Search
    wxButton *selectfile = new wxButton(Files, 3, _T("Selecet File"), wxPoint(50, 600), wxSize(100,20), wxSP_THIN_SASH);
    //File Display
    text.Create(Files,1, _T("File List..."),
                wxPoint(0, 40), wxSize(200,500), wxHSCROLL | wxTE_READONLY);

    Files->SetSizer(leftsizer);
    text.SetBackgroundColour(wxColour(255, 255, 255));
    text.SetForegroundColour(wxColour(55, 53, 47));

    //Right Splitter
    //file viewer and search tool
    wxSplitterWindow *rightsplitter = new wxSplitterWindow(leftsplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_THIN_SASH | wxSP_LIVE_UPDATE);
    //Panels
    wxPanel *Viewer = new wxPanel(rightsplitter);
    wxPanel *Searchbar = new wxPanel(rightsplitter);
    //text

    //top right sizer
    wxBoxSizer *rightsizer = new wxBoxSizer(wxHORIZONTAL);

    viewfile.Create(Viewer,1, _T("View Files Here..."),
                    wxPoint(0, 40), wxSize(995,760), wxTE_READONLY);
    viewfile.SetBackgroundColour(wxColour(255, 255, 255));
    viewfile.SetForegroundColour(wxColour(55, 53, 47));


    //search sizer
    wxBoxSizer *Searchbox = new wxBoxSizer(wxHORIZONTAL);

    wxTextCtrl *searchline = new wxTextCtrl(Searchbar, wxID_ANY, "Search", wxPoint(20, 20), wxSize(800, 20), wxTE_PROCESS_ENTER);

    wxButton *searchbutton = new wxButton(Searchbar, 2, _T("Search"),
                                          wxPoint(20, 0), wxSize(100,50), 0);


    //results sizer
    wxBoxSizer *Resultsbox = new wxBoxSizer(wxHORIZONTAL);
    wxTextCtrl *resultstext = new wxTextCtrl(Searchbar, wxID_ANY, "results", wxPoint(0, 50), wxSize(998, 400), wxSHAPED | wxTE_READONLY);
    resultstext->SetBackgroundColour(wxColour(255, 255, 255));
    resultstext->SetForegroundColour(wxColour(55, 53, 47));



    //
    Viewer->SetSizerAndFit(rightsizer);
    Searchbar->SetSizer(Searchbox);
    //add the text to box sizer
    //add the sizer to the panel

    //rightbottom1->Add(search);
    Searchbox->Add(searchline);
    Searchbox->Add(searchbutton);
    searchline->SetBackgroundColour(wxColour(255, 255, 255));
    searchline->SetForegroundColour(wxColour(55, 53, 47));
    Resultsbox->Add(resultstext);


    //setsizers into panel
    Searchbar->SetSizer(Searchbox);
    Searchbar->SetMinSize(wxDefaultSize);


    Files->SetBackgroundColour(wxColor(240, 240, 239));
    Viewer->SetBackgroundColour(wxColor(240, 240, 239));
    Searchbar->SetBackgroundColour(wxColor(240, 240, 239));

    //left splitter configuration
    //leftsplitter->SetMinimumPaneSize(20);
    leftsplitter->SplitVertically(Files, rightsplitter);
    leftsplitter->SetSashInvisible(1);

    //right splitter configuration
    rightsplitter->SetMinimumPaneSize(400);
    rightsplitter->SplitHorizontally(Viewer, Searchbar);
    rightsplitter->SetSashGravity(1.0);
    rightsplitter->SetBorderSize(0);

    rightsplitter->SetMinimumPaneSize(50);
    rightsplitter->SetBorderSize(0);

}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    std::string line = "Search ID" + std::to_string(event.GetId());
    SetStatusText(line);
    //wxLogMessage("This is a log message!");
}


void MyFrame::FileSearch(wxCommandEvent& event)
{
    //show status and event info
    std::string line = "Search ID" + std::to_string(event.GetId());
    SetStatusText(line);

    wxDir dir(wxDirSelector());

    if (!wxDirExists){
        std::cout << "no directory found";
    }else {
        text.Clear();

        puts("Enumerating object files in current directory:");

        wxString filename;
        bool cont = dir.GetFirst(&filename);
        while (cont) {
            //std::cout << filename << "\n";
            text.AppendText(wxString::Format(_T("%s\n"), filename.c_str()));
            cont = dir.GetNext(&filename);
        }
    }

    event.Skip();
}

void MyFrame::SearchText(wxCommandEvent& event)
{
    wxMessageBox("Fuction to be implemented","SearchText", wxOK | wxICON_INFORMATION);
    event.Skip();
}

void MyFrame::OnFileNameClick(wxCommandEvent& event)
{
    wxString file;
    wxFileDialog fdlog(this);

    // show file dialog and get the path to
    // the file that was selected.
    if(fdlog.ShowModal() != wxID_OK) return;
    file.Clear();
    file = fdlog.GetPath();

    wxString str;

    // open the file
    tfile.Open(file);

    //clear textctrl
    viewfile.Clear();

    // read the first line
    //str = tfile.GetFirstLine();
    //processLine(str); // placeholder, do whatever you want with the string

    // read all lines one by one
    // until the end of the file
    while(!tfile.Eof())
    {
        str = tfile.GetNextLine();
        //write to textctrl
        viewfile.AppendText(str + "\n"); // placeholder, do whatever you want with the string

    }
    event.Skip();
}