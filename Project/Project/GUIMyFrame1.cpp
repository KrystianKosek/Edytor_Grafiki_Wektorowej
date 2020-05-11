#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1(wxWindow* parent) : MyFrame1(nullptr), image_handler(new wxPNGHandler())
{
	wxImage::AddHandler(image_handler);
	_fileDialog = new wxFileDialog(this, _("Wybierz plik:"), _(""), _("result.jpg"), _(".jpg"), wxFD_SAVE);
	number_of_sides = 3;
	drawALine = false;
	drawACircle = false;
	isBegin = false;
	drawARectangle = false;
	drawingAFigureWithNSides = false;
	drawAFigureInCircle = false;
	sidesLeft = 0;
}

void GUIMyFrame1::panelOnLeftDown(wxMouseEvent& event) {
	// na razie nie używane
}
void GUIMyFrame1::panelOnLeftUp(wxMouseEvent& event) {
	// na razie nie używane
}
void GUIMyFrame1::panelOnMouseEvents(wxMouseEvent& event) {
	// rysowanie linii
	if (event.LeftDown() && drawALine) {
		wxPoint point = event.GetPosition();
		points[points.size() - 1].push_back(wxPoint(point.x, point.y));
	}
	// rysowanie tych dziwnych figur zlożonych z iluś tam boków
	else if ((event.LeftDown() && sidesLeft > 0) && drawingAFigureWithNSides) {
		sidesLeft--;
		wxPoint point = event.GetPosition();
		weirdFigures[weirdFigures.size() - 1].push_back(point);
		if (sidesLeft == 0) {
			weirdFigures[weirdFigures.size() - 1].push_back(weirdFigures[weirdFigures.size() - 1][0]);
			drawingAFigureWithNSides = false;
		}
	}
	// rysowanie okręgu
	else if ((event.LeftDown() && drawACircle) && isBegin) {
		wxPoint end = event.GetPosition();
		float x = abs(begin.x - end.x);
		float y = abs(begin.y - end.y);
		float r = sqrt(pow(x, 2) + pow(y, 2));
		circles.insert(std::make_pair(new wxPoint(begin), r));
		drawACircle = false;
		isBegin = false;
	}
	// rysowanie okręgu też
	else if (event.LeftDown() && drawACircle) {
		begin = event.GetPosition();
		isBegin = true;
	}
	// rysowanie prostokąta
	else if ((event.LeftDown() && drawARectangle) && isBegin) {
		wxPoint end = event.GetPosition();
		rectangles.insert(std::make_pair(new wxPoint(begin), new wxPoint(end)));
		isBegin = false;
		drawARectangle = false;
	}
	// rysowanie prostokąta też :)
	else if (event.LeftDown() && drawARectangle) {
		begin = event.GetPosition();
		isBegin = true;
	}

	// rysowanie figury wpisanej w okrąg
	else if ((event.LeftDown() && drawAFigureInCircle) && isBegin) {
		wxPoint end = event.GetPosition();
		float x = abs(begin.x - end.x);
		float y = abs(begin.y - end.y);
		float r = sqrt(pow(x, 2) + pow(y, 2));
		circles.insert(std::make_pair(new wxPoint(begin), r));
		x = begin.x;
		y = begin.y;
		figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x, y-r));
		for (int i = 1; i < number_of_sides; i++) {
			double alfa = 2. * M_PI / number_of_sides * i;
			if (alfa < M_PI/2.) 
				figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x-sin(alfa)*r, y-cos(alfa)*r));
			else if (alfa == M_PI/2.) 
				figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x-r, y));
			else if (alfa < M_PI) 
				figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x-sin(M_PI - alfa)*r, y +cos(M_PI - alfa)*r));
			else if (alfa == M_PI) 
				figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x, y+r));
			else if (alfa < 3/2.*M_PI) 
				figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x + sin(alfa-M_PI)*r, y +cos(alfa-M_PI)*r));
			else if (alfa == 3 / 2.*M_PI) 
				figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x+r, y));
			else if (alfa < 2.*M_PI) 
				figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x +sin(2*M_PI-alfa)*r,y -cos(2 * M_PI - alfa)*r));
		}
		figuresInCircles[figuresInCircles.size() - 1].push_back(figuresInCircles[figuresInCircles.size() - 1][0]);
		drawAFigureInCircle = false;
		isBegin = false;
	}
	// rysowanie okręgu też
	else if (event.LeftDown() && drawAFigureInCircle) {
		begin = event.GetPosition();
		isBegin = true;
	}

}

void GUIMyFrame1::m_panel1OnPaint(wxPaintEvent& event)
{
	wxClientDC dcClient(m_panel1);
	m_panel1->Refresh();
	m_panel1->Update();
	draw(dcClient);
}

void GUIMyFrame1::m_panel1OnUpdateUI(wxUpdateUIEvent& event)
{
	wxClientDC dcClient(m_panel1);
	draw(dcClient);
}

// rysowanie lini
void GUIMyFrame1::draw_line_buttonOnButtonClick(wxCommandEvent& event)
{
	if (drawingAFigureWithNSides) {
		return;
	}
	if (drawARectangle || drawACircle) {
		drawACircle = false;
		isBegin = false;
		drawACircle = false;
	}
	if (drawALine) {
		drawALine = false;
	}
	else {
		drawALine = true;
		points.push_back({});
	}
}

// Krzywa beziera???
void GUIMyFrame1::draw_curve_buttonOnButtonClick(wxCommandEvent& event)
{
	// TODO: Implement draw_curve_buttonOnButtonClick
}

// rysowanie prostokąta
void GUIMyFrame1::draw_rectangle_buttonOnButtonClick(wxCommandEvent& event)
{
	if (drawingAFigureWithNSides) {
		return;
	}
	if ((drawAFigureInCircle || drawALine) || drawACircle) {
		drawACircle = false;
		isBegin = false;
		drawALine = false;
	}
	if (!drawARectangle)
		drawARectangle = true;
	else {
		drawARectangle = false;
		isBegin = false;
	}
}

// rysowanie okręgu
void GUIMyFrame1::draw_circle_buttonOnButtonClick(wxCommandEvent& event)
{
	if (drawingAFigureWithNSides) {
		return;
	}
	if ((drawARectangle || drawALine) || drawAFigureInCircle) {
		drawARectangle = false;
		isBegin = false;
		drawALine = false;
	}
	if (!drawACircle)
		drawACircle = true;
	else {
		drawACircle = false;
		isBegin = false;
	}
}

// rysowanie tych dziwnych figur
void GUIMyFrame1::any_figure_button4OnButtonClick(wxCommandEvent& event)
{
	if (drawingAFigureWithNSides) {
		return;
	}
	if (((drawARectangle || drawALine) || drawACircle) || drawAFigureInCircle) {
		drawARectangle = false;
		drawACircle = false;
		isBegin = false;
		drawALine = false;
	}
	drawingAFigureWithNSides = true;
	sidesLeft = number_of_sides;
	weirdFigures.push_back({});
}

// rysowanie figur wpisanych w okrąg
void GUIMyFrame1::figure_int_circle_button12OnButtonClick(wxCommandEvent& event)
{
	if (drawingAFigureWithNSides) {
		return;
	}
	if ((drawARectangle || drawALine) || drawACircle) {
		drawARectangle = false;
		isBegin = false;
		drawALine = false;
	}
	if (!drawAFigureInCircle) {
		drawAFigureInCircle = true;
		figuresInCircles.push_back({});
	}
	else {
		drawAFigureInCircle = false;
		isBegin = false;
	}
}

void GUIMyFrame1::filling_checkBox1OnCheckBox(wxCommandEvent& event)
{
	// TODO: Implement filling_checkBox1OnCheckBox
}

void GUIMyFrame1::figure_sides_choice1OnChoice(wxCommandEvent& event)
{
	// TODO: Implement figure_sides_choice1OnChoice
	number_of_sides = event.GetSelection() + 3;
}

void GUIMyFrame1::line_color_button7OnButtonClick(wxCommandEvent& event)
{
	// do zmiany, bo na razie koloruje wszystko co było, jest i będzie narysowane
	// ale myśle, że trzeba to pod sam koniec zmienić
	wxColourDialog colourDialog(this);
	if (colourDialog.ShowModal() == wxID_OK)
		line_colour = colourDialog.GetColourData().GetColour();
	Refresh();
}

void GUIMyFrame1::save_image_button8OnButtonClick(wxCommandEvent& event)
{
	// do zmiany na jsona, ale ja bym to zostawił na sam koniec, 
	// bo jeszcze nie znamy dokładnej formy przetrzymywania punktów wszystkich figur
	wxClientDC dcClient(m_panel1);
	wxBufferedDC dcBuffer(&dcClient);

	PrepareDC(dcBuffer);
	wxInitAllImageHandlers();

	wxString filePath;

	if (_fileDialog->ShowModal() == wxID_OK) {
		Refresh();

		//wybor sciezki
		filePath = _fileDialog->GetPath();

		//pobieramy wielkosc panelu
		wxSize size = m_panel1->GetVirtualSize();
		wxBitmap bitmapToSave(size);

		wxMemoryDC memory;
		memory.SelectObject(bitmapToSave);

		//przydzielenie odpowiedniej ilosci pamieci dla rozmiaru obrazu
		memory.Blit(0, 0, size.GetX(), size.GetY(), &dcBuffer, 0, 0, wxCOPY, true);

		//konwersja na image
		wxImage imageToSave = bitmapToSave.ConvertToImage();
		imageToSave.SaveFile(filePath, wxBITMAP_TYPE_JPEG);
	}
	Refresh();
}

void GUIMyFrame1::figure_color_filling_button10OnButtonClick(wxCommandEvent& event)
{
	wxColourDialog colourDialog(this);
	if (colourDialog.ShowModal() == wxID_OK)
		filling_colour = colourDialog.GetColourData().GetColour();
	Refresh();
}

void GUIMyFrame1::rotate_figure_button11OnButtonClick(wxCommandEvent& event)
{
	// TODO: Implement rotate_figure_button11OnButtonClick
}

void GUIMyFrame1::move_figure_button12OnButtonClick(wxCommandEvent& event)
{
	// TODO: Implement move_figure_button12OnButtonClick
}

void GUIMyFrame1::size_change_button13OnButtonClick(wxCommandEvent& event)
{
	// TODO: Implement size_change_button13OnButtonClick
}

void GUIMyFrame1::load_image_button9OnButtonClick(wxCommandEvent& event)
{
	// TODO: Implement load_image_button9OnButtonClick
}

void GUIMyFrame1::move_wierzcholek_button14OnButtonClick(wxCommandEvent& event)
{
	// TODO: Implement move_wierzcholek_button14OnButtonClick
}

void GUIMyFrame1::delete_figure_button15OnButtonClick(wxCommandEvent& event)
{
	// TODO: Implement delete_figure_button15OnButtonClick
}

void GUIMyFrame1::draw(wxClientDC & dcClient) {
	wxBufferedDC dcBuffer(&dcClient);
	PrepareDC(dcBuffer);
	dcBuffer.Clear();
	dcBuffer.SetBrush(wxBrush(*wxWHITE_BRUSH));

	dcBuffer.SetPen(wxPen(wxColor(line_colour), 1));
	if (points.size() > 0) {
		for (unsigned i = 0; i < points.size(); i++) {
			for (unsigned j = 1; j < points[i].size(); j++) {
				dcBuffer.DrawLine(points[i][j - 1], points[i][j]);
			}
		}
	}

	if (figuresInCircles.size() > 0) {
		for (unsigned i = 0; i < figuresInCircles.size(); i++) {
			for (unsigned j = 1; j < figuresInCircles[i].size(); j++) {
				dcBuffer.DrawLine(figuresInCircles[i][j - 1], figuresInCircles[i][j]);
			}
		}
	}

	dcBuffer.SetBrush(wxBrush(*wxTRANSPARENT_BRUSH));
	for (auto itr = circles.begin(); itr != circles.end(); itr++) {
		dcBuffer.DrawCircle(*(itr->first), itr->second);
	}
	for (auto itr = rectangles.begin(); itr != rectangles.end(); itr++) {
		wxPoint leftUp = wxPoint(itr->first->x, itr->second->y);
		wxPoint rightDown = wxPoint(itr->second->x, itr->first->y);
		dcBuffer.DrawLine(*(itr->first), leftUp);
		dcBuffer.DrawLine(*(itr->first), rightDown);
		dcBuffer.DrawLine(*(itr->second), leftUp);
		dcBuffer.DrawLine(*(itr->second), rightDown);
	}

	if (weirdFigures.size() > 0) {
		for (unsigned i = 0; i < weirdFigures.size(); i++) {
			for (unsigned j = 1; j < weirdFigures[i].size(); j++) {
				dcBuffer.DrawLine(weirdFigures[i][j - 1], weirdFigures[i][j]);
			}
		}
	}
}

GUIMyFrame1::~GUIMyFrame1() {
	delete _fileDialog;
}