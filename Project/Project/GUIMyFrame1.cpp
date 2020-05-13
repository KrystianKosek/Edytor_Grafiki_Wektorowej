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

	m_panel1->Bind(wxEVT_LEFT_DOWN, &GUIMyFrame1::panelOnLeftDown, this);
	m_panel1->Bind(wxEVT_LEFT_UP, &GUIMyFrame1::panelOnLeftUp, this);
	m_panel1->Bind(wxEVT_MOTION, &GUIMyFrame1::panelOnMotion, this);
	m_panel1->Bind(wxEVT_PAINT, &GUIMyFrame1::m_panel1OnPaint, this);
}

void GUIMyFrame1::panelOnLeftDown(wxMouseEvent& event) {
	// rysowanie krzywej beziera
	if (drawingABezierCurve) {
		wxPoint currentPoint = event.GetPosition();
		for (std::vector<wxPoint>::iterator iterator = bezierCurve.begin(); iterator != bezierCurve.end(); iterator++)
		{
			if ((std::abs(iterator->x - currentPoint.x) + std::abs(iterator->y - currentPoint.y)) < 10)
			{
				selected = iterator;
				selected->x = currentPoint.x;
				selected->y = currentPoint.y;
			}
		}
		if (selected == bezierCurve.end())
		{
			selected = bezierCurve.end();
			selected--;
			bezierCurve.push_back(currentPoint);
		}
		m_panel1->Refresh();
	}
	// rysowanie linii
	else if (event.LeftDown() && drawALine) {
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
	else if (event.LeftDown() && drawACircle) {
		begin = event.GetPosition();
		isBegin = true;
		circles.insert({ new wxPoint(begin), 1 });
		m_panel1->Refresh();
	}
	// rysowanie prostokąta
	else if (event.LeftDown() && drawARectangle) {
		begin = event.GetPosition();
		isBegin = true;
		rectangles.insert(std::make_pair(new wxPoint(begin), new wxPoint(begin.x + 1, begin.y + 1)));
	}
	// rysowanie figury wpisanej w okrąg
	else if (event.LeftDown() && drawAFigureInCircle) {
		begin = event.GetPosition();
		wxPoint end = wxPoint(begin.x + 1, begin.y + 1);
		float x = abs(begin.x - end.x);
		float y = abs(begin.y - end.y);
		float r = sqrt(pow(x, 2) + pow(y, 2));
		circles.insert({ new wxPoint(begin), r });
		isBegin = true;
		x = begin.x;
		y = begin.y;
		figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x, y - r));
		for (int i = 1; i < number_of_sides; i++) {
			double alfa = 2. * M_PI / number_of_sides * i;
			if (alfa < M_PI / 2.)
				figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x - sin(alfa)*r, y - cos(alfa)*r));
			else if (alfa == M_PI / 2.)
				figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x - r, y));
			else if (alfa < M_PI)
				figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x - sin(M_PI - alfa)*r, y + cos(M_PI - alfa)*r));
			else if (alfa == M_PI)
				figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x, y + r));
			else if (alfa < 3 / 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x + sin(alfa - M_PI)*r, y + cos(alfa - M_PI)*r));
			else if (alfa == 3 / 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x + r, y));
			else if (alfa < 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1].push_back(wxPoint(x + sin(2 * M_PI - alfa)*r, y - cos(2 * M_PI - alfa)*r));
		}
		figuresInCircles[figuresInCircles.size() - 1].push_back(figuresInCircles[figuresInCircles.size() - 1][0]);

		m_panel1->Refresh();
	}
}
void GUIMyFrame1::panelOnLeftUp(wxMouseEvent& event) {
	// rysowanie krzywej beziera
	if (drawingABezierCurve) {
		selected = bezierCurve.end();
		m_panel1->Refresh();
	}
	// rysowanie okręgu
	else if (drawACircle) {
		wxPoint endOfFigure = event.GetPosition();
		float x = abs(begin.x - endOfFigure.x);
		float y = abs(begin.y - endOfFigure.y);
		float r = sqrt(pow(x, 2) + pow(y, 2));
		std::multimap<wxPoint *, float>::iterator it = circles.begin();
		while (it != circles.end()) {
			if (it->first->x == begin.x && it->first->y == begin.y) {
				break;
			}
			it++;
		}
		it->second = r;
		isBegin = false;
		drawACircle = false;
		m_panel1->Refresh();
	}
	// rysowanie prostokąta
	else if (drawARectangle) {
		wxPoint endOfFigure = event.GetPosition();
		std::multimap<wxPoint *, wxPoint *>::iterator it = rectangles.begin();
		while (it != rectangles.end()) {
			if (it->first->x == begin.x && it->first->y == begin.y) {
				break;
			}
			it++;
		}
		it->second = new wxPoint(endOfFigure);
		drawARectangle = false;
		m_panel1->Refresh();
	}
	// rysowanie figury wpisanej w okrąg
	else if (drawAFigureInCircle) {
		wxPoint end = event.GetPosition();
		float x = abs(begin.x - end.x);
		float y = abs(begin.y - end.y);
		float r = sqrt(pow(x, 2) + pow(y, 2));
		std::multimap<wxPoint *, float>::iterator it = circles.begin();
		while (it != circles.end()) {
			if (it->first->x == begin.x && it->first->y == begin.y) {
				break;
			}
			it++;
		}
		it->second = r;
		x = begin.x;
		y = begin.y;
		figuresInCircles[figuresInCircles.size() - 1][0] = wxPoint(x, y - r);
		for (int i = 1; i < number_of_sides; i++) {
			double alfa = 2. * M_PI / number_of_sides * i;
			if (alfa < M_PI / 2.)
				figuresInCircles[figuresInCircles.size() - 1][i] = wxPoint(x - sin(alfa)*r, y - cos(alfa)*r);
			else if (alfa == M_PI / 2.)
				figuresInCircles[figuresInCircles.size() - 1][i] = wxPoint(x - r, y);
			else if (alfa < M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i] = wxPoint(x - sin(M_PI - alfa)*r, y + cos(M_PI - alfa)*r);
			else if (alfa == M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i] = wxPoint(x, y + r);
			else if (alfa < 3 / 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i] = wxPoint(x + sin(alfa - M_PI)*r, y + cos(alfa - M_PI)*r);
			else if (alfa == 3 / 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i] = wxPoint(x + r, y);
			else if (alfa < 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i] = wxPoint(x + sin(2 * M_PI - alfa)*r, y - cos(2 * M_PI - alfa)*r);
		}
		figuresInCircles[figuresInCircles.size() - 1][figuresInCircles[figuresInCircles.size() - 1].size() - 1] = figuresInCircles[figuresInCircles.size() - 1][0];
		drawAFigureInCircle = false;
		m_panel1->Refresh();
	}
}

void GUIMyFrame1::panelOnMotion(wxMouseEvent& event) {
	// rysowanie krzywej beziera
	if ((drawingABezierCurve && event.LeftIsDown()) && selected != bezierCurve.end())
	{
		wxPoint p = event.GetPosition();
		selected->x = p.x;
		selected->y = p.y;
		m_panel1->Refresh();
	}
	// rysowanie okręgu
	else if (drawACircle && event.LeftIsDown()) {
		wxPoint endOfFigure = event.GetPosition();
		float x = abs(begin.x - endOfFigure.x);
		float y = abs(begin.y - endOfFigure.y);
		float r = sqrt(pow(x, 2) + pow(y, 2));
		std::multimap<wxPoint *, float>::iterator it = circles.begin();
		while (it != circles.end()) {
			if (it->first->x == begin.x && it->first->y == begin.y) {
				break;
			}
			it++;
		}
		it->second = r;
		m_panel1->Refresh();
	}
	// rysowanie prostokąta
	else if (event.LeftIsDown() && drawARectangle) {
		wxPoint endOfFigure = event.GetPosition();
		std::multimap<wxPoint *, wxPoint *>::iterator it = rectangles.begin();
		while (it != rectangles.end()) {
			if (it->first->x == begin.x && it->first->y == begin.y) {
				break;
			}
			it++;
		}
		it->second = new wxPoint(endOfFigure);
		m_panel1->Refresh();
	}
	// rysowanie figury wpisanej w okrąg
	else if (event.LeftIsDown() && drawAFigureInCircle) {
		wxPoint end = event.GetPosition();
		float x = abs(begin.x - end.x);
		float y = abs(begin.y - end.y);
		float r = sqrt(pow(x, 2) + pow(y, 2));
		std::multimap<wxPoint *, float>::iterator it = circles.begin();
		while (it != circles.end()) {
			if (it->first->x == begin.x && it->first->y == begin.y) {
				break;
			}
			it++;
		}
		it->second = r;
		x = begin.x;
		y = begin.y;
		figuresInCircles[figuresInCircles.size() - 1][0] = wxPoint(x, y - r);
		for (int i = 1; i < number_of_sides; i++) {
			double alfa = 2. * M_PI / number_of_sides * i;
			if (alfa < M_PI / 2.)
				figuresInCircles[figuresInCircles.size() - 1][i] = wxPoint(x - sin(alfa)*r, y - cos(alfa)*r);
			else if (alfa == M_PI / 2.)
				figuresInCircles[figuresInCircles.size() - 1][i] = wxPoint(x - r, y);
			else if (alfa < M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i] = wxPoint(x - sin(M_PI - alfa)*r, y + cos(M_PI - alfa)*r);
			else if (alfa == M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i] = wxPoint(x, y + r);
			else if (alfa < 3 / 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i] = wxPoint(x + sin(alfa - M_PI)*r, y + cos(alfa - M_PI)*r);
			else if (alfa == 3 / 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i] = wxPoint(x + r, y);
			else if (alfa < 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i] = wxPoint(x + sin(2 * M_PI - alfa)*r, y - cos(2 * M_PI - alfa)*r);
		}
		figuresInCircles[figuresInCircles.size() - 1][figuresInCircles[figuresInCircles.size() - 1].size() - 1] = figuresInCircles[figuresInCircles.size() - 1][0];

		m_panel1->Refresh();
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
	if ((drawARectangle || drawACircle) || drawingABezierCurve) {
		drawACircle = false;
		isBegin = false;
		drawACircle = false;
		drawingABezierCurve = false;
	}
	if (drawALine) {
		drawALine = false;
	}
	else {
		drawALine = true;
		points.push_back({});
	}
}

// Krzywa beziera
void GUIMyFrame1::draw_curve_buttonOnButtonClick(wxCommandEvent& event)
{
	if (drawingAFigureWithNSides) {
		return;
	}
	if ((drawARectangle || drawACircle) || drawALine) {
		drawACircle = false;
		isBegin = false;
		drawACircle = false;
		drawALine = false;
	}
	if (drawingABezierCurve) {
		drawingABezierCurve = false;
	}
	else {
		drawingABezierCurve = true;
	}
}

// rysowanie prostokąta
void GUIMyFrame1::draw_rectangle_buttonOnButtonClick(wxCommandEvent& event)
{
	if (drawingAFigureWithNSides) {
		return;
	}
	if (drawingABezierCurve) {
		drawingABezierCurve = false;
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
	if (drawingABezierCurve) {
		drawingABezierCurve = false;
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
	if (drawingABezierCurve) {
		drawingABezierCurve = false;
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
	if (drawingABezierCurve) {
		drawingABezierCurve = false;
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
	
	// rysowanie prostych
	if (points.size() > 0) {
		for (unsigned i = 0; i < points.size(); i++) {
			for (unsigned j = 1; j < points[i].size(); j++) {
				dcBuffer.DrawLine(points[i][j - 1], points[i][j]);
			}
		}
	}
	// rysowanie figur wpisanych w okrąg
	if (figuresInCircles.size() > 0) {
		for (unsigned i = 0; i < figuresInCircles.size(); i++) {
			for (unsigned j = 1; j < figuresInCircles[i].size(); j++) {
				dcBuffer.DrawLine(figuresInCircles[i][j - 1], figuresInCircles[i][j]);
			}
		}
	}
	// rysowanie okręgów
	dcBuffer.SetBrush(wxBrush(*wxTRANSPARENT_BRUSH));
	for (auto itr = circles.begin(); itr != circles.end(); itr++) {
		dcBuffer.DrawCircle(*(itr->first), itr->second);
	}
	// rysowanie prostokątów
	for (auto itr = rectangles.begin(); itr != rectangles.end(); itr++) {
		wxPoint leftUp = wxPoint(itr->first->x, itr->second->y);
		wxPoint rightDown = wxPoint(itr->second->x, itr->first->y);
		dcBuffer.DrawRectangle(wxRect(leftUp, rightDown));
	}
	// rysowanie tych dziwnych figur
	if (weirdFigures.size() > 0) {
		for (unsigned i = 0; i < weirdFigures.size(); i++) {
			for (unsigned j = 1; j < weirdFigures[i].size(); j++) {
				dcBuffer.DrawLine(weirdFigures[i][j - 1], weirdFigures[i][j]);
			}
		}
	}
	// rysowanie krzywych beziera
	if (bezierCurve.size() > 2)
	{
		dcBuffer.DrawSpline(bezierCurve.size(), &(bezierCurve[0]));
	}
	for (std::vector<wxPoint>::iterator iterator = bezierCurve.begin(); iterator != bezierCurve.end(); iterator++)
	{
		dcBuffer.DrawCircle(*iterator, 5);
	}
	if (bezierCurve.size() > 2) {
		if (selected != bezierCurve.end())
		{
			dcBuffer.SetPen(*wxRED_PEN);
			dcBuffer.SetBrush(*wxRED_BRUSH);
			dcBuffer.DrawCircle(*selected, 4);
		}
	}
}

GUIMyFrame1::~GUIMyFrame1() {
	delete _fileDialog;
}