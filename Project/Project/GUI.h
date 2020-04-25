///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/stattext.h>
#include <wx/gbsizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_panel1;
		wxButton* draw_line_button;
		wxButton* draw_curve_button;
		wxButton* draw_rectangle_button;
		wxButton* draw_circle_button;
		wxButton* any_figure_button4;
		wxButton* figure_int_circle_button12;
		wxCheckBox* filling_checkBox1;
		wxChoice* figure_sides_choice1;
		wxButton* line_color_button7;
		wxButton* save_image_button8;
		wxButton* figure_color_filling_button10;
		wxButton* rotate_figure_button11;
		wxButton* move_figure_button12;
		wxButton* size_change_button13;
		wxButton* load_image_button9;
		wxButton* move_wierzcholek_button14;
		wxButton* delete_figure_button15;
		wxStaticText* m_staticText1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void m_panel1OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void m_panel1OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void draw_line_buttonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void draw_curve_buttonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void draw_rectangle_buttonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void draw_circle_buttonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void any_figure_button4OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void figure_int_circle_button12OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void filling_checkBox1OnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void figure_sides_choice1OnChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void line_color_button7OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void save_image_button8OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void figure_color_filling_button10OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void rotate_figure_button11OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void move_figure_button12OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void size_change_button13OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void load_image_button9OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void move_wierzcholek_button14OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void delete_figure_button15OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Edytor Grafiki Wektorowej - Projekt Adrian Góral, Krystian Kosek i Bartosz Mikołajczyk"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 999,690 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MyFrame1();
	
};

#endif //__GUI_H__
