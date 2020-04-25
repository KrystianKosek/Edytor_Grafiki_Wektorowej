///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame4::MyFrame4( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );
	
	bSizer2->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );
	
	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	draw_line_button = new wxButton( this, wxID_ANY, wxT("prosta"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( draw_line_button, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	draw_curve_button = new wxButton( this, wxID_ANY, wxT("krzywa"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( draw_curve_button, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	draw_rectangle_button = new wxButton( this, wxID_ANY, wxT("prostąk"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( draw_rectangle_button, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	draw_circle_button = new wxButton( this, wxID_ANY, wxT("okrąg"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( draw_circle_button, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	any_figure_button4 = new wxButton( this, wxID_ANY, wxT("wielokąt\n"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( any_figure_button4, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	figure_int_circle_button12 = new wxButton( this, wxID_ANY, wxT("wielokąt \nwpisany"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( figure_int_circle_button12, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	filling_checkBox1 = new wxCheckBox( this, wxID_ANY, wxT("wypełnienie"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	filling_checkBox1->SetValue(true); 
	gbSizer1->Add( filling_checkBox1, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	wxString figure_sides_choice1Choices[] = { wxT("3"), wxT("4"), wxT("5"), wxT("6"), wxT("7"), wxT("8"), wxT("9"), wxT("10"), wxT("11"), wxT("12"), wxT("13"), wxT("14"), wxT("15"), wxT("16"), wxT("17"), wxT("18"), wxT("19"), wxT("20") };
	int figure_sides_choice1NChoices = sizeof( figure_sides_choice1Choices ) / sizeof( wxString );
	figure_sides_choice1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, figure_sides_choice1NChoices, figure_sides_choice1Choices, 0 );
	figure_sides_choice1->SetSelection( 0 );
	gbSizer1->Add( figure_sides_choice1, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	line_color_button7 = new wxButton( this, wxID_ANY, wxT("kolor linii"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( line_color_button7, wxGBPosition( 4, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	save_image_button8 = new wxButton( this, wxID_ANY, wxT("zapisz obraz"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( save_image_button8, wxGBPosition( 8, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_button10 = new wxButton( this, wxID_ANY, wxT("kolor \nwypełnienia"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_button10, wxGBPosition( 5, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	rotate_figure_button11 = new wxButton( this, wxID_ANY, wxT("obróć"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( rotate_figure_button11, wxGBPosition( 6, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	move_figure_button12 = new wxButton( this, wxID_ANY, wxT("przesuń"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( move_figure_button12, wxGBPosition( 6, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_button13 = new wxButton( this, wxID_ANY, wxT("zmień\nrozmiar"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_button13, wxGBPosition( 5, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	load_image_button9 = new wxButton( this, wxID_ANY, wxT("wczytaj obraz"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( load_image_button9, wxGBPosition( 8, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_button14 = new wxButton( this, wxID_ANY, wxT("przesuń\nwierzchołek"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_button14, wxGBPosition( 7, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	delete_figure_button15 = new wxButton( this, wxID_ANY, wxT("usuń"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( delete_figure_button15, wxGBPosition( 7, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("boki wielokąta"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	gbSizer1->Add( m_staticText1, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer1->Add( gbSizer1, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	draw_line_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::draw_line_buttonOnButtonClick ), NULL, this );
	draw_curve_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::draw_curve_buttonOnButtonClick ), NULL, this );
	draw_rectangle_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::draw_rectangle_buttonOnButtonClick ), NULL, this );
	any_figure_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::any_figure_button4OnButtonClick ), NULL, this );
	figure_int_circle_button12->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::figure_int_circle_button12OnButtonClick ), NULL, this );
	filling_checkBox1->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame4::filling_checkBox1OnCheckBox ), NULL, this );
	figure_sides_choice1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyFrame4::figure_sides_choice1OnChoice ), NULL, this );
	line_color_button7->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::line_color_button7OnButtonClick ), NULL, this );
	save_image_button8->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::save_image_button8OnButtonClick ), NULL, this );
	rotate_figure_button11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::rotate_figure_button11OnButtonClick ), NULL, this );
	move_figure_button12->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::move_figure_button12OnButtonClick ), NULL, this );
	load_image_button9->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::load_image_button9OnButtonClick ), NULL, this );
	delete_figure_button15->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::delete_figure_button15OnButtonClick ), NULL, this );
}

MyFrame4::~MyFrame4()
{
	// Disconnect Events
	draw_line_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::draw_line_buttonOnButtonClick ), NULL, this );
	draw_curve_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::draw_curve_buttonOnButtonClick ), NULL, this );
	draw_rectangle_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::draw_rectangle_buttonOnButtonClick ), NULL, this );
	any_figure_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::any_figure_button4OnButtonClick ), NULL, this );
	figure_int_circle_button12->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::figure_int_circle_button12OnButtonClick ), NULL, this );
	filling_checkBox1->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame4::filling_checkBox1OnCheckBox ), NULL, this );
	figure_sides_choice1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyFrame4::figure_sides_choice1OnChoice ), NULL, this );
	line_color_button7->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::line_color_button7OnButtonClick ), NULL, this );
	save_image_button8->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::save_image_button8OnButtonClick ), NULL, this );
	rotate_figure_button11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::rotate_figure_button11OnButtonClick ), NULL, this );
	move_figure_button12->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::move_figure_button12OnButtonClick ), NULL, this );
	load_image_button9->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::load_image_button9OnButtonClick ), NULL, this );
	delete_figure_button15->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::delete_figure_button15OnButtonClick ), NULL, this );
	
}
