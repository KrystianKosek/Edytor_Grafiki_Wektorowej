#include "GUIMyFrame1.h"
#include <algorithm>

GUIMyFrame1::GUIMyFrame1(wxWindow* parent) : MyFrame1(nullptr)
{
	//wxImage::AddHandler(image_handler);
	_fileDialog = new wxFileDialog(this, _("Wybierz plik:"), _(""), _("result.json"), _(".json"), wxFD_SAVE);
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
		//for (std::vector<wxPoint>::iterator iterator = bezierCurve.begin(); iterator != bezierCurve.end(); iterator++)
		std::vector<wxPoint>::iterator iterator = bezierArray[bezierArray.size() - 1].begin();
		while (iterator != bezierArray[bezierArray.size() - 1].end())
		{
			if ((std::abs(iterator->x - currentPoint.x) + std::abs(iterator->y - currentPoint.y)) < 10)
			{
				selected = iterator;
				selected->x = currentPoint.x;
				selected->y = currentPoint.y;
			}
			iterator++;
		}
		//if (selected == bezierCurve.end())
		if (selected == bezierArray[bezierArray.size() -1].end())
		{
			//selected = bezierCurve.end();
			selected--;
			//bezierCurve.push_back(currentPoint);
			bezierArray[bezierArray.size() - 1].push_back(currentPoint);
			//bezierCurveColor = line_colour;
		}
		m_panel1->Refresh();
	}
	// rysowanie linii
	else if (event.LeftDown() && drawALine) {
		wxPoint point = event.GetPosition();
		points[points.size() - 1].push_back({ wxPoint(point.x, point.y), line_colour});
	}
	// rysowanie tych dziwnych figur zlożonych z iluś tam boków
	else if (event.LeftDown() && drawingAFigureWithNSides) {
		if (sidesLeft == 0)
			sidesLeft = number_of_sides;
		if (sidesLeft == number_of_sides)
			weirdFigures.push_back({});
		sidesLeft--;
		wxPoint point = event.GetPosition();
		weirdFigures[weirdFigures.size() - 1].push_back({ point, line_colour });
		if (sidesLeft == 0) {
			weirdFigures[weirdFigures.size() - 1].push_back({ weirdFigures[weirdFigures.size() - 1][0].first, line_colour });
			//weirdFigures.push_back({});
			//drawingAFigureWithNSides = false;
		}
	}
	// rysowanie okręgu
	else if (event.LeftDown() && drawACircle) {
		begin = event.GetPosition();
		isBegin = true;
		circles.insert({ new wxPoint(begin), {1, line_colour} });
		//m_panel1->Refresh();
	}
	// rysowanie prostokąta
	else if (event.LeftDown() && drawARectangle) {
		begin = event.GetPosition();
		isBegin = true;
		rectangles.push_back({ { new wxPoint(begin), new wxPoint(begin.x + 1, begin.y + 1) }, line_colour});
	}
	// rysowanie figury wpisanej w okrąg
	else if (event.LeftDown() && drawAFigureInCircle) {
		figuresInCircles.push_back({});
		begin = event.GetPosition();
		wxPoint end = wxPoint(begin.x + 1, begin.y + 1);
		float x = abs(begin.x - end.x);
		float y = abs(begin.y - end.y);
		float r = sqrt(pow(x, 2) + pow(y, 2));
		circles.insert({ new wxPoint(begin), {r, line_colour} });
		isBegin = true;
		x = begin.x;
		y = begin.y;
		figuresInCircles[figuresInCircles.size() - 1].push_back({ wxPoint(x, y - r), line_colour });
		for (int i = 1; i < number_of_sides; i++) {
			double alfa = 2. * M_PI / number_of_sides * i;
			if (alfa < M_PI / 2.)
				figuresInCircles[figuresInCircles.size() - 1].push_back({ wxPoint(x - sin(alfa)*r, y - cos(alfa)*r), line_colour });
			else if (alfa == M_PI / 2.)
				figuresInCircles[figuresInCircles.size() - 1].push_back({ wxPoint(x - r, y), line_colour });
			else if (alfa < M_PI)
				figuresInCircles[figuresInCircles.size() - 1].push_back({ wxPoint(x - sin(M_PI - alfa)*r, y + cos(M_PI - alfa)*r), line_colour });
			else if (alfa == M_PI)
				figuresInCircles[figuresInCircles.size() - 1].push_back({ wxPoint(x, y + r), line_colour });
			else if (alfa < 3 / 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1].push_back({ wxPoint(x + sin(alfa - M_PI)*r, y + cos(alfa - M_PI)*r), line_colour });
			else if (alfa == 3 / 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1].push_back({ wxPoint(x + r, y), line_colour });
			else if (alfa < 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1].push_back({ wxPoint(x + sin(2 * M_PI - alfa)*r, y - cos(2 * M_PI - alfa)*r), line_colour });
		}
		figuresInCircles[figuresInCircles.size() - 1].push_back(figuresInCircles[figuresInCircles.size() - 1][0]);

		m_panel1->Refresh();
	}
}
void GUIMyFrame1::panelOnLeftUp(wxMouseEvent& event) {
	// rysowanie krzywej beziera
	if (drawingABezierCurve) {
		//selected = bezierCurve.end();
		selected = bezierArray[bezierArray.size() - 1].end();
		//bezierArray[bezierArray.size() - 1] = bezierCurve;
		m_panel1->Refresh();
	}
	// rysowanie okręgu
	else if (drawACircle) {
		wxPoint endOfFigure = event.GetPosition();
		float x = abs(begin.x - endOfFigure.x);
		float y = abs(begin.y - endOfFigure.y);
		float r = sqrt(pow(x, 2) + pow(y, 2));
		std::multimap<wxPoint *, std::pair<float, wxColour>>::iterator it = circles.begin();
		while (it != circles.end()) {
			if (it->first->x == begin.x && it->first->y == begin.y) {
				break;
			}
			it++;
		}
		it->second.first = r;
		
		m_panel1->Refresh();
	}
	// rysowanie prostokąta
	else if (drawARectangle) {
		wxPoint endOfFigure = event.GetPosition();
		std::list<std::pair<std::pair<wxPoint *, wxPoint *>, wxColour>>::iterator it = rectangles.begin();
		while (it != rectangles.end()) {
			if (it->first.first->x == begin.x && it->first.first->y == begin.y) {
				break;
			}
			it++;
		}
		it->first.second = new wxPoint(endOfFigure);
		isBegin = false;
		m_panel1->Refresh();
	}
	// rysowanie figury wpisanej w okrąg
	else if (drawAFigureInCircle) {
		wxPoint end = event.GetPosition();
		float x = abs(begin.x - end.x);
		float y = abs(begin.y - end.y);
		float r = sqrt(pow(x, 2) + pow(y, 2));
		std::multimap<wxPoint *, std::pair<float, wxColour>>::iterator it = circles.begin();
		while (it != circles.end()) {
			if (it->first->x == begin.x && it->first->y == begin.y) {
				break;
			}
			it++;
		}
		it->second.first = r;
		x = begin.x;
		y = begin.y;
		figuresInCircles[figuresInCircles.size() - 1][0].first = wxPoint(x, y - r);

		for (int i = 1; i < number_of_sides; i++) {
			double alfa = 2. * M_PI / number_of_sides * i;
			if (alfa < M_PI / 2.)
				figuresInCircles[figuresInCircles.size() - 1][i].first = wxPoint(x - sin(alfa)*r, y - cos(alfa)*r);
			else if (alfa == M_PI / 2.)
				figuresInCircles[figuresInCircles.size() - 1][i].first = wxPoint(x - r, y);
			else if (alfa < M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i].first = wxPoint(x - sin(M_PI - alfa)*r, y + cos(M_PI - alfa)*r);
			else if (alfa == M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i].first = wxPoint(x, y + r);
			else if (alfa < 3 / 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i].first = wxPoint(x + sin(alfa - M_PI)*r, y + cos(alfa - M_PI)*r);
			else if (alfa == 3 / 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i].first = wxPoint(x + r, y);
			else if (alfa < 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i].first = wxPoint(x + sin(2 * M_PI - alfa)*r, y - cos(2 * M_PI - alfa)*r);
		}
		figuresInCircles[figuresInCircles.size() - 1][figuresInCircles[figuresInCircles.size() - 1].size() - 1] = figuresInCircles[figuresInCircles.size() - 1][0];
		//drawAFigureInCircle = false;
		m_panel1->Refresh();
	}
}

void GUIMyFrame1::turn_off_drawing()
{
	drawACircle = false;
	drawAFigureInCircle = false;
	isBegin = false;
	drawALine = false;
	drawARectangle = false;
	drawAFigureInCircle = false;
	drawingABezierCurve = false;
	drawingAFigureWithNSides = false;
	sidesLeft = 0;
}

void GUIMyFrame1::panelOnMotion(wxMouseEvent& event) {
	// rysowanie krzywej beziera
	//if ((drawingABezierCurve && event.LeftIsDown()) && selected != bezierCurve.end() && bezierCurve.size() > 0)
	if ((drawingABezierCurve && event.LeftIsDown()) && selected != bezierArray[bezierArray.size() - 1].end() && bezierArray[bezierArray.size() - 1].size() > 0)
	{
		wxPoint p = event.GetPosition();
		//selected = bezierCurve.end();
		//--selected;
		selected->x = p.x;
		selected->y = p.y;
		//bezierArray[bezierArray.size() - 1] = bezierCurve;
		m_panel1->Refresh();
	}
	// rysowanie okręgu
	else if (drawACircle && event.LeftIsDown()) {
		wxPoint endOfFigure = event.GetPosition();
		float x = abs(begin.x - endOfFigure.x);
		float y = abs(begin.y - endOfFigure.y);
		float r = sqrt(pow(x, 2) + pow(y, 2));
		std::multimap<wxPoint *, std::pair<float, wxColour>>::iterator it = circles.begin();
		while (it != circles.end()) {
			if (it->first->x == begin.x && it->first->y == begin.y) {
				break;
			}
			it++;
		}
		it->second.first = r;
		m_panel1->Refresh();
	}
	// rysowanie prostokąta
	else if (event.LeftIsDown() && drawARectangle) {
		wxPoint endOfFigure = event.GetPosition();
		std::list<std::pair<std::pair<wxPoint *, wxPoint *>, wxColour>>::iterator it = rectangles.begin();
		while (it != rectangles.end()) {
			if (it->first.first->x == begin.x && it->first.first->y == begin.y) {
				break;
			}
			it++;
		}
		it->first.second = new wxPoint(endOfFigure);
		m_panel1->Refresh();
	}
	// rysowanie figury wpisanej w okrąg
	else if (event.LeftIsDown() && drawAFigureInCircle) {
		wxPoint end = event.GetPosition();
		float x = abs(begin.x - end.x);
		float y = abs(begin.y - end.y);
		float r = sqrt(pow(x, 2) + pow(y, 2));
		std::multimap<wxPoint *, std::pair<float, wxColour>>::iterator it = circles.begin();
		while (it != circles.end()) {
			if (it->first->x == begin.x && it->first->y == begin.y) {
				break;
			}
			it++;
		}
		it->second.first = r;
		x = begin.x;
		y = begin.y;
		figuresInCircles[figuresInCircles.size() - 1][0].first = wxPoint(x, y - r);
		for (int i = 1; i < number_of_sides; i++) {
			double alfa = 2. * M_PI / number_of_sides * i;
			if (alfa < M_PI / 2.)
				figuresInCircles[figuresInCircles.size() - 1][i].first = wxPoint(x - sin(alfa)*r, y - cos(alfa)*r);
			else if (alfa == M_PI / 2.)
				figuresInCircles[figuresInCircles.size() - 1][i].first = wxPoint(x - r, y);
			else if (alfa < M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i].first = wxPoint(x - sin(M_PI - alfa)*r, y + cos(M_PI - alfa)*r);
			else if (alfa == M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i].first = wxPoint(x, y + r);
			else if (alfa < 3 / 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i].first = wxPoint(x + sin(alfa - M_PI)*r, y + cos(alfa - M_PI)*r);
			else if (alfa == 3 / 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i].first = wxPoint(x + r, y);
			else if (alfa < 2.*M_PI)
				figuresInCircles[figuresInCircles.size() - 1][i].first = wxPoint(x + sin(2 * M_PI - alfa)*r, y - cos(2 * M_PI - alfa)*r);
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
	if ((drawARectangle || drawACircle) || drawingABezierCurve || drawingAFigureWithNSides || drawAFigureInCircle) {
		drawACircle = false;
		isBegin = false;
		drawARectangle = false;
		drawingABezierCurve = false;
		drawAFigureInCircle = false;
		drawingAFigureWithNSides = false;
	}
	if (drawALine) {
		points.push_back({});
	}
	else {
		drawALine = true;
		points.push_back({});
	}
}

// Krzywa beziera
void GUIMyFrame1::draw_curve_buttonOnButtonClick(wxCommandEvent& event)
{
	if ((drawARectangle || drawACircle) || drawALine || drawingAFigureWithNSides || drawAFigureInCircle) {
		drawACircle = false;
		isBegin = false;
		drawAFigureInCircle = false;
		drawALine = false;
		drawARectangle = false;
		drawingAFigureWithNSides = false;
	}
	if (drawingABezierCurve) {
		//bezierArray.push_back(bezierCurve);
		bezierArray.push_back({});
		bezierCurveColors.push_back({});
		//bezierCurve.clear();
		return;
	}
	else {
		//bezierArray.push_back(bezierCurve);
		bezierArray.push_back({});
		bezierCurveColors.push_back({});
		//bezierCurve.clear();
		drawingABezierCurve = true;
	}
}

// rysowanie prostokąta
void GUIMyFrame1::draw_rectangle_buttonOnButtonClick(wxCommandEvent& event)
{
	if (drawAFigureInCircle || drawALine || drawACircle || drawingAFigureWithNSides || drawingABezierCurve) {
		drawACircle = false;
		isBegin = false;
		drawALine = false;
		drawingAFigureWithNSides = false;
		drawingABezierCurve = false;
		drawAFigureInCircle = false;
	}
	if (!drawARectangle)
		drawARectangle = true;
	else {
		return;
	}
}

// rysowanie okręgu
void GUIMyFrame1::draw_circle_buttonOnButtonClick(wxCommandEvent& event)
{
	if ((drawARectangle || drawALine) || drawAFigureInCircle || drawingABezierCurve || drawingAFigureWithNSides) {
		drawARectangle = false;
		isBegin = false;
		drawALine = false;
		drawingABezierCurve = false;
		drawingAFigureWithNSides = false;
		drawAFigureInCircle = false;
	}
	if (!drawACircle)
		drawACircle = true;
	else {
		return;
	}
}

// rysowanie tych dziwnych figur
void GUIMyFrame1::any_figure_button4OnButtonClick(wxCommandEvent& event)
{
	if (drawingAFigureWithNSides) {
		return;
	}
	if (drawARectangle || drawALine || drawACircle || drawAFigureInCircle || drawingABezierCurve) 
	{
		drawARectangle = false;
		drawACircle = false;
		isBegin = false;
		drawALine = false;
		drawingABezierCurve = false;
		drawAFigureInCircle = false;
	}
	drawingAFigureWithNSides = true;
	sidesLeft = number_of_sides;
	//weirdFigures.push_back({});
}

// rysowanie figur wpisanych w okrąg
void GUIMyFrame1::figure_int_circle_button12OnButtonClick(wxCommandEvent& event)
{
	if (drawARectangle || drawALine || drawACircle || drawingABezierCurve || drawingAFigureWithNSides) {
		drawARectangle = false;
		drawALine = false;
		drawingABezierCurve = false;
		drawACircle = false;
		isBegin = false;
		drawingAFigureWithNSides = false;
	}
	if (!drawAFigureInCircle) {
		drawAFigureInCircle = true;
	}
	else {
		return;
	}
}

//void GUIMyFrame1::filling_checkBox1OnCheckBox(wxCommandEvent& event)
//{
	// TODO: Implement filling_checkBox1OnCheckBox
//}

void GUIMyFrame1::figure_sides_choice1OnChoice(wxCommandEvent& event)
{
	number_of_sides = event.GetSelection() + 3;
}

void GUIMyFrame1::line_color_button7OnButtonClick(wxCommandEvent& event)
{
	wxColourDialog colourDialog(this);
	if (colourDialog.ShowModal() == wxID_OK)
		line_colour = colourDialog.GetColourData().GetColour();
	if (drawingABezierCurve)
		bezierCurveColors[bezierCurveColors.size() - 1] = line_colour;
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
		string filename = _fileDialog->GetPath();

		ofstream _file;
		_file.open(filename);
		json bezier_array;
		json _event;
		json obj;
		json lines_array;
		json cicrles_array;
		json rectangles_array;
		json weirdFigures_array;
		json tmp_line;
		json figures_in_circles_array;
		if (bezierArray.size() > 0)
		{
			for (int i=0; i<bezierArray.size(); i++)
			//for (const auto& x : bezierArray)
			{
				const auto& x = bezierArray[i];
				//if (bezierCurve.size() > 0) {
				for (const auto& v : x) {
					obj["color"] = bezierCurveColors[i].GetRGB();
					obj["x"] = v.x;
					obj["y"] = v.y;
					tmp_line.push_back(obj);
				}
				bezier_array.push_back(tmp_line);
				obj.clear();
				tmp_line.clear();
				
			}
			_event["bezier_curve"] = bezier_array;
		}
		if (points.size() > 0) {
			for (const auto& v : points) {
				for (const auto& z : v) {
					obj["color"] = z.second.GetRGB();
					obj["x"] = z.first.x;
					obj["y"] = z.first.y;
					tmp_line.push_back(obj);
				}
				lines_array.push_back(tmp_line);
				tmp_line.clear();
				obj.clear();
			}
			_event["lines_list"] = lines_array;
		}
		if (circles.size() > 0) {
			for_each(circles.begin(), circles.end(), [&cicrles_array, &obj](auto v) {
				obj["color"] = v.second.second.GetRGB();
				obj["radius"] = v.second.first;
				obj["x"] = v.first->x;
				obj["y"] = v.first->y;
				cicrles_array.push_back(obj); });
			obj.clear();
			_event["circles"] = cicrles_array;
		}
		if (rectangles.size() > 0) {
			for (const auto& v : rectangles) {
				obj["color"] = v.second.GetRGB();
				obj["x1"] = v.first.first->x;
				obj["x2"] = v.first.second->x;
				obj["y1"] = v.first.first->y;
				obj["y2"] = v.first.second->y;
				rectangles_array.push_back(obj);
			}
			_event["rectangles"] = rectangles_array;
			obj.clear();
		}
		if (weirdFigures.size() > 0) {
			for (const auto& v : weirdFigures) {
				for (const auto& z : v) {
					obj["color"] = z.second.GetRGB();
					obj["x"] = z.first.x;
					obj["y"] = z.first.y;
					tmp_line.push_back(obj);
				}
				weirdFigures_array.push_back(tmp_line);
				tmp_line.clear();
				obj.clear();
			}
			_event["weird_figures"] = weirdFigures_array;
		}
		if (figuresInCircles.size() > 0) {
			for (const auto& v : figuresInCircles) {
				for (const auto& z : v) {
					obj["color"] = z.second.GetRGB();
					obj["x"] = z.first.x;
					obj["y"] = z.first.y;
					tmp_line.push_back(obj);
				}
				figures_in_circles_array.push_back(tmp_line);
				tmp_line.clear();
				obj.clear();
			}
			_event["figures_in_circles"] = figures_in_circles_array;
		}

		_file << _event;
		_file.close();
	}
	Refresh();
}

/*void GUIMyFrame1::figure_color_filling_button10OnButtonClick(wxCommandEvent& event)
{
	wxColourDialog colourDialog(this);
	if (colourDialog.ShowModal() == wxID_OK)
		filling_colour = colourDialog.GetColourData().GetColour();
	Refresh();
}*/

/*void GUIMyFrame1::rotate_figure_button11OnButtonClick(wxCommandEvent& event)
{
	// TODO: Implement rotate_figure_button11OnButtonClick
}*/

/*void GUIMyFrame1::move_figure_button12OnButtonClick(wxCommandEvent& event)
{
	// TODO: Implement move_figure_button12OnButtonClick
}*/

//void GUIMyFrame1::size_change_button13OnButtonClick(wxCommandEvent& event)
//{
	// TODO: Implement size_change_button13OnButtonClick
//}

void GUIMyFrame1::load_image_button9OnButtonClick(wxCommandEvent& event)
{
	wxFileDialog WxOpenFileDialog(this, wxT("Wybierz plik"), wxT(""), wxT(""), wxT("Json file (*.json)|*.json"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (WxOpenFileDialog.ShowModal() == wxID_OK)
	{
		string _save_name = WxOpenFileDialog.GetPath();
		std::ifstream ifs(_save_name);
		if (ifs.is_open()) {
			bezierArray.clear();
			//bezierCurve.clear();
			points.clear();
			circles.clear();
			rectangles.clear();
			weirdFigures.clear();
			figuresInCircles.clear();
			turn_off_drawing();
			json _read;
			ifs >> _read;
			if (_read["bezier_curve"].size() > 0) {
				std::vector<wxPoint> bezierCurve;
				for (const auto& v : _read["bezier_curve"])
				{
					wxColor _color;
					for (const auto& z : v) {
						_color.SetRGB(z["color"].get<int>());
						int x = z["x"].get<int>();
						int y = z["y"].get<int>();
						bezierCurve.push_back(wxPoint(x, y));
					}
					bezierCurveColors.push_back(_color);
					selected = bezierCurve.end();
					--selected;
					bezierArray.push_back(bezierCurve);
					bezierCurve.clear();
				}
			}
			if (_read["lines_list"].size() > 0) {
				for (const auto& v : _read["lines_list"]) {
					std::list<std::pair<wxPoint, wxColour>> _tmp;
					for (const auto& z : v) {
						wxColor _color;
						_color.SetRGB(z["color"].get<int>());
						int x = z["x"].get<int>();
						int y = z["y"].get<int>();
						_tmp.push_back(make_pair(wxPoint(x, y), _color));
					}
					points.push_back(_tmp);
				}
			}
			if (_read["circles"].size() > 0) {
				for (const auto& v : _read["circles"]) {
					wxColor _color;
					_color.SetRGB(v["color"].get<int>());
					float _radius = v["radius"].get<float>();
					int x = v["x"].get<int>();
					int y = v["y"].get<int>();
					circles.emplace(make_pair(new wxPoint(x, y) , make_pair(_radius, _color)));
				}
			}
			if (_read["rectangles"].size() > 0) {
				for (const auto& v : _read["rectangles"]) {
					wxColor _color;
					_color.SetRGB(v["color"].get<int>());
					int x1 = v["x1"].get<int>();
					int y1 = v["y1"].get<int>();
					int x2 = v["x2"].get<int>();
					int y2 = v["y2"].get<int>();
					rectangles.push_back(make_pair(make_pair(new wxPoint(x1, y1), new wxPoint(x2, y2)), _color));
				}
			}
			if (_read["weird_figures"].size() > 0) {
				std::vector<std::pair<wxPoint, wxColour>> _tmp;
				for (const auto& v : _read["weird_figures"]) {
					for (const auto& z : v) {
						wxColor _color;
						_color.SetRGB(z["color"].get<int>());
						int x = z["x"].get<int>();
						int y = z["y"].get<int>();
						_tmp.push_back(make_pair(wxPoint(x, y), _color));
					}
					weirdFigures.push_back(_tmp);
				}
			}
			if (_read["figures_in_circles"].size() > 0) {
				for (const auto& v : _read["figures_in_circles"]) {
					std::vector<std::pair<wxPoint, wxColour>> _tmp;
					for (const auto& z : v) {
						wxColor _color;
						_color.SetRGB(z["color"].get<int>());
						int x = z["x"].get<int>();
						int y = z["y"].get<int>();
						_tmp.push_back(make_pair(wxPoint(x, y), _color));
					}
					figuresInCircles.push_back(_tmp);
				}
			}
		}
		ifs.close();
	}
	Refresh();
}

/*void GUIMyFrame1::move_wierzcholek_button14OnButtonClick(wxCommandEvent& event)
{
	// TODO: Implement move_wierzcholek_button14OnButtonClick
}*/

//void GUIMyFrame1::delete_figure_button15OnButtonClick(wxCommandEvent& event)
//{
	// TODO: Implement delete_figure_button15OnButtonClick
//}

void GUIMyFrame1::draw(wxClientDC & dcClient) {
	wxBufferedDC dcBuffer(&dcClient);
	PrepareDC(dcBuffer);
	dcBuffer.Clear();
	dcBuffer.SetBrush(wxBrush(*wxWHITE_BRUSH));

	dcBuffer.SetPen(wxPen(wxColor(line_colour), 1));
	
	// rysowanie prostych
	if (points.size() > 0) {
		for (unsigned i = 0; i < points.size(); i++) {
			for (auto itr = points[i].begin(); itr != points[i].end(); itr++) {
				dcBuffer.SetPen(wxPen(wxColor(itr->second), 1));
				auto tmp = itr;
				if (tmp != points[i].begin()) {
					--tmp;
					dcBuffer.DrawLine((tmp->first), (itr->first));
				}
			}
		}
	}
	// rysowanie figur wpisanych w okrąg
	if (figuresInCircles.size() > 0) {
		for (unsigned i = 0; i < figuresInCircles.size(); i++) {
			for (unsigned j = 1; j < figuresInCircles[i].size(); j++) {
				dcBuffer.SetPen(wxPen(wxColor(figuresInCircles[i][j - 1].second), 1));
				dcBuffer.DrawLine(figuresInCircles[i][j - 1].first, figuresInCircles[i][j].first);
			}
		}
	}
	// rysowanie okręgów
	dcBuffer.SetBrush(wxBrush(*wxTRANSPARENT_BRUSH));
	for (auto itr = circles.begin(); itr != circles.end(); itr++) {
		dcBuffer.SetPen(wxPen(wxColor(itr->second.second), 1));
		dcBuffer.DrawCircle(*(itr->first), itr->second.first);
	}
	// rysowanie prostokątów
	for (auto itr = rectangles.begin(); itr != rectangles.end(); itr++) {
		dcBuffer.SetPen(wxPen(wxColor(itr->second), 1));
		wxPoint leftUp = wxPoint(itr->first.first->x, itr->first.second->y);
		wxPoint rightDown = wxPoint(itr->first.second->x, itr->first.first->y);
		dcBuffer.DrawRectangle(wxRect(leftUp, rightDown));
	}
	// rysowanie tych dziwnych figur
	if (weirdFigures.size() > 0) {
		for (unsigned i = 0; i < weirdFigures.size(); i++) {
			for (unsigned j = 1; j < weirdFigures[i].size(); j++) {
				dcBuffer.SetPen(wxPen(wxColor(weirdFigures[i][j - 1].second), 1));
				dcBuffer.DrawLine(weirdFigures[i][j - 1].first, weirdFigures[i][j].first);
			}
		}
	}
	for (auto i = 0; i < bezierArray.size(); i++)
	{
		std::vector<wxPoint> bezierCurve = bezierArray[i];
		// rysowanie krzywych beziera
		if (bezierCurve.size() > 2)
		{
			dcBuffer.SetPen(wxPen(wxColor(bezierCurveColors[i]), 1));
			dcBuffer.DrawSpline(bezierCurve.size(), &(bezierCurve[0]));
		}
		if (i == bezierArray.size() - 1)
			for (std::vector<wxPoint>::iterator iterator = bezierCurve.begin(); iterator != bezierCurve.end(); iterator++)
			{
				dcBuffer.DrawCircle(*iterator, 5);
			}
		//if (bezierCurve.size() > 2) {
		//	if (selected != bezierCurve.end())
		//	{
		//		dcBuffer.SetPen(*wxRED_PEN);
		//		dcBuffer.SetBrush(*wxRED_BRUSH);
		//		dcBuffer.DrawCircle(*selected, 4);
		//	}
		//}
	}
}

GUIMyFrame1::~GUIMyFrame1() {
	delete _fileDialog;
}