#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent ): MyFrame1(nullptr), image_handler(new wxPNGHandler())
{
	wxImage::AddHandler(image_handler);
	_fileDialog = new wxFileDialog(this, _("Wybierz plik:"), _(""), _("result.jpg"), _(".jpg"), wxFD_SAVE);
	number_of_sides = 3;
	drawALine = false;
	drawACircle = false;
	isBegin = false;
	drawARectangle = false;
}

void GUIMyFrame1::panelOnLeftDown(wxMouseEvent& event) {
	// na razie nie używane
}
void GUIMyFrame1::panelOnLeftUp(wxMouseEvent& event) {
	// na razie nie używane
}
void GUIMyFrame1::panelOnMouseEvents(wxMouseEvent& event) {
	// sprawdzamy czy użytkownik chce rysować linie
	if (event.LeftDown() && drawALine) {
		wxPoint point = event.GetPosition();
		std::ofstream zapis("onMouseEvents.txt");
		zapis << "ASDASDA" << point.x << " " << point.y;
		zapis.close();
		drawALine = false;
		points.push_back(wxPoint(point.x, point.y));
	}
	else if ((event.LeftDown() && drawACircle) && isBegin) {
		wxPoint end = event.GetPosition();
		float x = abs(begin.x - end.x);
		float y = abs(begin.y - end.y);
		float r = sqrt(pow(x, 2) + pow(y, 2));
		circles.insert(std::make_pair(new wxPoint(begin), r));
		drawACircle = false;
		isBegin = false;
	}
	else if (event.LeftDown() && drawACircle) {
		begin = event.GetPosition();
		isBegin = true;
	}
	else if ((event.LeftDown() && drawARectangle) && isBegin) {
		wxPoint end = event.GetPosition();
		rectangles.insert(std::make_pair(new wxPoint(begin), new wxPoint(end)));
		isBegin = false;
		drawARectangle = false;
	}
	else if (event.LeftDown() && drawARectangle) {
		begin = event.GetPosition();
		isBegin = true;
	}
	
}

void GUIMyFrame1::m_panel1OnPaint( wxPaintEvent& event )
{
	wxClientDC dcClient(m_panel1);
	m_panel1->Refresh();
	m_panel1->Update();
	draw(dcClient);
}

void GUIMyFrame1::m_panel1OnUpdateUI( wxUpdateUIEvent& event )
{
	wxClientDC dcClient(m_panel1);
	draw(dcClient);
}

void GUIMyFrame1::draw_line_buttonOnButtonClick(wxCommandEvent& event )
{
	drawALine = true;
}

// Krzywa beziera???
void GUIMyFrame1::draw_curve_buttonOnButtonClick( wxCommandEvent& event )
{
// TODO: Implement draw_curve_buttonOnButtonClick
}

void GUIMyFrame1::draw_rectangle_buttonOnButtonClick( wxCommandEvent& event )
{
	if (drawACircle)
		drawARectangle = false;
	else
		drawARectangle = true;
}

void GUIMyFrame1::draw_circle_buttonOnButtonClick( wxCommandEvent& event )
{
	if (drawARectangle)
		drawACircle = false;
	else
		drawACircle = true;
}

void GUIMyFrame1::any_figure_button4OnButtonClick( wxCommandEvent& event )
{
// TODO: Implement any_figure_button4OnButtonClick
}

void GUIMyFrame1::figure_int_circle_button12OnButtonClick( wxCommandEvent& event )
{
// TODO: Implement figure_int_circle_button12OnButtonClick
}

void GUIMyFrame1::filling_checkBox1OnCheckBox( wxCommandEvent& event )
{
// TODO: Implement filling_checkBox1OnCheckBox
}

void GUIMyFrame1::figure_sides_choice1OnChoice( wxCommandEvent& event )
{
// TODO: Implement figure_sides_choice1OnChoice
	number_of_sides = event.GetSelection() + 3;
}

void GUIMyFrame1::line_color_button7OnButtonClick( wxCommandEvent& event )
{
	wxColourDialog colourDialog(this);
	if (colourDialog.ShowModal() == wxID_OK)
		line_colour = colourDialog.GetColourData().GetColour();
	Refresh();
}

void GUIMyFrame1::save_image_button8OnButtonClick( wxCommandEvent& event )
{
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

void GUIMyFrame1::figure_color_filling_button10OnButtonClick( wxCommandEvent& event )
{
	wxColourDialog colourDialog(this);
	if (colourDialog.ShowModal() == wxID_OK)
		filling_colour = colourDialog.GetColourData().GetColour();
	Refresh();
}

void GUIMyFrame1::rotate_figure_button11OnButtonClick( wxCommandEvent& event )
{
// TODO: Implement rotate_figure_button11OnButtonClick
}

void GUIMyFrame1::move_figure_button12OnButtonClick( wxCommandEvent& event )
{
// TODO: Implement move_figure_button12OnButtonClick
}

void GUIMyFrame1::size_change_button13OnButtonClick( wxCommandEvent& event )
{
// TODO: Implement size_change_button13OnButtonClick
}

void GUIMyFrame1::load_image_button9OnButtonClick( wxCommandEvent& event )
{
// TODO: Implement load_image_button9OnButtonClick
}

void GUIMyFrame1::move_wierzcholek_button14OnButtonClick( wxCommandEvent& event )
{
// TODO: Implement move_wierzcholek_button14OnButtonClick
}

void GUIMyFrame1::delete_figure_button15OnButtonClick( wxCommandEvent& event )
{
// TODO: Implement delete_figure_button15OnButtonClick
}

void GUIMyFrame1::draw(wxClientDC & dcClient) {
	wxBufferedDC dcBuffer(&dcClient);
	PrepareDC(dcBuffer);
	dcBuffer.Clear();
	dcBuffer.SetBrush(wxBrush(*wxWHITE_BRUSH));

	dcBuffer.SetPen(wxPen(wxColor(line_colour), 1));
	for (unsigned i = 1; i < points.size(); i++) {
		dcBuffer.DrawLine(points[i - 1], points[i]);
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
}

GUIMyFrame1::~GUIMyFrame1() {
	delete _fileDialog;
}