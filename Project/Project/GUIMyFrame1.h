﻿#ifndef __GUIMyFrame1__
#define __GUIMyFrame1__

/**
@file
Subclass of MyFrame1, which is generated by wxFormBuilder.
*/

#include "GUI.h"

//// end generated include
#include <wx/filedlg.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>
#include <wx/graphics.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <utility>
#include <list>

/** Implementing MyFrame1 */


class GUIMyFrame1 : public MyFrame1
{
protected:
	// Handlers for MyFrame1 events.
	void panelOnLeftDown(wxMouseEvent& event);
	void panelOnLeftUp(wxMouseEvent& event);
	void panelOnMotion(wxMouseEvent& event);
	void m_panel1OnPaint(wxPaintEvent& event);
	void m_panel1OnUpdateUI(wxUpdateUIEvent& event);
	void draw_line_buttonOnButtonClick(wxCommandEvent& event);
	void draw_curve_buttonOnButtonClick(wxCommandEvent& event);
	void draw_rectangle_buttonOnButtonClick(wxCommandEvent& event);
	void draw_circle_buttonOnButtonClick(wxCommandEvent& event);
	void any_figure_button4OnButtonClick(wxCommandEvent& event);
	void figure_int_circle_button12OnButtonClick(wxCommandEvent& event);
	void filling_checkBox1OnCheckBox(wxCommandEvent& event);
	void figure_sides_choice1OnChoice(wxCommandEvent& event);
	void line_color_button7OnButtonClick(wxCommandEvent& event);
	void save_image_button8OnButtonClick(wxCommandEvent& event);
	void figure_color_filling_button10OnButtonClick(wxCommandEvent& event);
	void rotate_figure_button11OnButtonClick(wxCommandEvent& event);
	void move_figure_button12OnButtonClick(wxCommandEvent& event);
	void size_change_button13OnButtonClick(wxCommandEvent& event);
	void load_image_button9OnButtonClick(wxCommandEvent& event);
	void move_wierzcholek_button14OnButtonClick(wxCommandEvent& event);
	void delete_figure_button15OnButtonClick(wxCommandEvent& event);

public:
	/** Constructor */
	GUIMyFrame1(wxWindow* parent);
	//// end generated class members
	void draw(wxClientDC & dcClient);
	~GUIMyFrame1();

private:
	wxColour line_colour, filling_colour;
	wxImageHandler * image_handler;
	wxFileDialog * _fileDialog;
	int number_of_sides;
	std::vector<std::list<std::pair<wxPoint, wxColour>>> points;
	bool drawALine;	// ta zmienna jak jest true, to znaczy że rysujemy linie aktualnie
	bool drawACircle;	// ta zmienna jak jest jest true to znaczy że rysujemy okrąg
	std::multimap<wxPoint *, std::pair<float, wxColour>> circles;	// mapa punktów, klucz jest środkiem okręgu, wartość to prmień
	wxPoint begin;	// punkt startowy używany do rysowania okregów ( środek okręgu )
	bool isBegin;	// jest true w momencie gdy użytkownik kliknął i wybrał środek rysowanego okręgu
	bool drawARectangle;	// jeśli jest true to rysujemy prostokąt
	//std::multimap<wxPoint *, wxPoint *> rectangles;		// mapa punktów, klucz jest pkt dolnym lewym, wartośc jest pkt górnym prawym
	std::list<std::pair<std::pair<wxPoint *, wxPoint *>, wxColour>> rectangles;
	bool drawingAFigureWithNSides;	// jesli true to rysujemy te dziwne figury
	int sidesLeft;	// zmienna informuje nas ile jeszcze zostało boków do narysowania ( dziwne figury )
	std::vector<std::vector<std::pair<wxPoint, wxColour>>> weirdFigures;	// zbiór dziwnych figur
	bool drawAFigureInCircle;	// jesli true to rysujemy figury wpisane w okrąg
	std::vector<std::vector<wxPoint>> figuresInCircles;	// figury wpisane w okrąg
	bool drawingABezierCurve;
	std::vector<wxPoint> bezierCurve;	// vector z punktami, punkt odchylenia
	std::vector<wxPoint>::iterator selected;	// aktualnie wybrany pkt poprzez wcisniecie lewego klawisza
};

#endif // __GUIMyFrame1__