// -*- mode: c++; c-file-style: "linux"; c-basic-offset: 2; indent-tabs-mode:
// nil -*-
//
//  Copyright (C) 2004-2015 Andrej Vodopivec <andrej.vodopivec@gmail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
//
//  SPDX-License-Identifier: GPL-2.0+

#include "Plot3dWiz.h"

#include <wx/artprov.h>
#include <wx/config.h>

Plot3DWiz::Plot3DWiz(wxWindow *parent, int id, Configuration *cfg,
                     const wxString &title, const wxPoint &pos,
                     const wxSize &size, long style)
  : wxDialog(parent, id, title, pos, size, style) {
  label_2 = new wxStaticText(this, -1, _("Expression"));
  text_ctrl_1 = new BTextCtrl(this, -1, cfg, wxEmptyString, wxDefaultPosition);
  label_3 = new wxStaticText(this, -1, _("Variable:"));
  text_ctrl_2 =
    new BTextCtrl(this, -1, cfg, wxS("x"), wxDefaultPosition, wxSize(40, -1));
  label_4 = new wxStaticText(this, -1, _("From:"));
  text_ctrl_3 = new BTextCtrl(this, -1, cfg, wxEmptyString, wxDefaultPosition,
                              wxSize(70, -1));
  label_5 = new wxStaticText(this, -1, _("To:"));
  text_ctrl_4 = new BTextCtrl(this, -1, cfg, wxEmptyString, wxDefaultPosition,
                              wxSize(70, -1));
  label_6 = new wxStaticText(this, -1, _("Variable:"));
  text_ctrl_5 =
    new BTextCtrl(this, -1, cfg, wxS("y"), wxDefaultPosition, wxSize(40, -1));
  label_7 = new wxStaticText(this, -1, _("From:"));
  text_ctrl_6 = new BTextCtrl(this, -1, cfg, wxEmptyString, wxDefaultPosition,
                              wxSize(70, -1));
  label_8 = new wxStaticText(this, -1, _("To:"));
  text_ctrl_7 = new BTextCtrl(this, -1, cfg, wxEmptyString, wxDefaultPosition,
                              wxSize(70, -1));
  label_9 = new wxStaticText(this, -1, _("Grid:"));
  text_ctrl_8 = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition,
                               wxSize(70, -1), wxSP_ARROW_KEYS, 0, 100, 30);
  text_ctrl_8->SetValue(30);
  label_10 = new wxStaticText(this, -1, wxS("x"));
  text_ctrl_9 = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition,
                               wxSize(70, -1), wxSP_ARROW_KEYS, 0, 100, 30);
  text_ctrl_9->SetValue(30);
  label_11 = new wxStaticText(this, -1, _("Format:"));
  const wxString combo_box_1_choices[] = {_("default"), _("inline"),
    wxS("gnuplot"), wxS("xmaxima")};
  combo_box_1 =
    new wxComboBox(this, -1, wxEmptyString, wxDefaultPosition,
		   wxSize(150, -1), 4, combo_box_1_choices, wxCB_DROPDOWN);
  label_12 = new wxStaticText(this, -1, _("Options:"));
  const wxString combo_box_2_choices[] = {
    wxS("set pm3d at b"),
    wxS("set pm3d at s; unset surf; unset colorbox"),
    wxS("set pm3d map; unset surf"),
    wxS("set hidden3d"),
    wxS("set mapping spherical"),
    wxS("set mapping cylindrical")};
  combo_box_2 =
    new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
		   wxSize(250, -1), 6, combo_box_2_choices, wxCB_DROPDOWN);
  combo_box_2->Connect(wxEVT_COMBOBOX, wxCommandEventHandler(Plot3DWiz::OnCombobox), NULL, this);

  check_box_1 = new wxCheckBox(this, -1, _("&pm3d"));
  label_13 = new wxStaticText(this, -1, _("Plot to file:"));
  text_ctrl_10 = new BTextCtrl(this, -1, cfg, wxEmptyString, wxDefaultPosition,
                               wxSize(250, -1));
  button_3 = new wxBitmapButton(
				this, wxID_ANY,
				wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_HELP_BROWSER));
  button_3->Connect(wxEVT_BUTTON, wxCommandEventHandler(Plot3DWiz::OnFileBrowse), NULL, this);
  static_line_1 = new wxStaticLine(this, -1);
#if defined __WXMSW__
  button_1 = new wxButton(this, wxID_OK, _("OK"));
  button_2 = new wxButton(this, wxID_CANCEL, _("Cancel"));
#else
  button_1 = new wxButton(this, wxID_CANCEL, _("Cancel"));
  button_2 = new wxButton(this, wxID_OK, _("OK"));
#endif

  type = cartesian;

  set_properties();
  do_layout();
}

void Plot3DWiz::set_properties() {
  SetTitle(_("Plot 3D"));
  text_ctrl_3->SetValue(wxS("-5"));
  text_ctrl_4->SetValue(wxS("5"));
  text_ctrl_6->SetValue(wxS("-5"));
  text_ctrl_7->SetValue(wxS("5"));

  button_3->SetToolTip(_("Browse"));

  bool pm3dValue;
#if defined __WXMSW__
  button_1->SetDefault();
  pm3dValue = true;
#else
  button_2->SetDefault();
#endif

  int selection = 1;
  wxConfig::Get()->Read(wxS("Wiz/Plot3D/format"), &selection);
  wxConfig::Get()->Read(wxS("Wiz/Plot3D/pm3d"), &pm3dValue);

  combo_box_1->SetSelection(selection);
  check_box_1->SetValue(pm3dValue);

  text_ctrl_1->SetFocus();
}

void Plot3DWiz::do_layout() {
  wxFlexGridSizer *grid_sizer_1 = new wxFlexGridSizer(4, 1, 0, 0);
  wxBoxSizer *sizer_1 = new wxBoxSizer(wxHORIZONTAL);
  wxFlexGridSizer *grid_sizer_2 = new wxFlexGridSizer(7, 2, 0, 0);
  wxBoxSizer *sizer_2 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *sizer_3 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *sizer_4 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *sizer_5 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *sizer_6 = new wxBoxSizer(wxHORIZONTAL);
  grid_sizer_2->Add(label_2, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL,
                    5);
  grid_sizer_2->Add(text_ctrl_1, 1, wxEXPAND | wxALL, 5);
  grid_sizer_2->Add(label_3, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL,
                    5);
  sizer_2->Add(text_ctrl_2, 0, wxALL, 5);
  sizer_2->Add(label_4, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
  sizer_2->Add(text_ctrl_3, 0, wxALL, 5);
  sizer_2->Add(label_5, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
  sizer_2->Add(text_ctrl_4, 0, wxALL, 5);
  grid_sizer_2->Add(sizer_2, 1, wxEXPAND, 0);
  grid_sizer_2->Add(label_6, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL,
                    5);
  sizer_3->Add(text_ctrl_5, 0, wxALL, 5);
  sizer_3->Add(label_7, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
  sizer_3->Add(text_ctrl_6, 0, wxALL, 5);
  sizer_3->Add(label_8, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
  sizer_3->Add(text_ctrl_7, 0, wxALL, 5);
  grid_sizer_2->Add(sizer_3, 1, wxEXPAND, 0);
  grid_sizer_2->Add(label_9, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL,
                    5);
  sizer_4->Add(text_ctrl_8, 0, wxALL, 5);
  sizer_4->Add(label_10, 0,
               wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  sizer_4->Add(text_ctrl_9, 0, wxALL, 5);
  grid_sizer_2->Add(sizer_4, 1, wxEXPAND, 0);
  grid_sizer_2->Add(label_11, 0,
                    wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 5);
  grid_sizer_2->Add(combo_box_1, 0, wxALL, 5);
  grid_sizer_2->Add(label_12, 0,
                    wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sizer_5->Add(combo_box_2, 0, wxALL, 5);
  sizer_5->Add(check_box_1, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
  grid_sizer_2->Add(sizer_5, 1, wxEXPAND, 0);
  grid_sizer_2->Add(label_13, 0,
                    wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sizer_6->Add(text_ctrl_10, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
  sizer_6->Add(button_3, 0, wxALL, 5);
  grid_sizer_2->Add(sizer_6, 1, wxEXPAND, 0);
  grid_sizer_1->Add(grid_sizer_2, 1, wxEXPAND, 0);
  grid_sizer_1->Add(static_line_1, 0, wxEXPAND | wxLEFT | wxRIGHT, 2);
  sizer_1->Add(button_1, 0, wxALL, 5);
  sizer_1->Add(button_2, 0, wxALL, 5);
  grid_sizer_1->Add(sizer_1, 1, wxALIGN_RIGHT, 0);
  SetAutoLayout(true);
  SetSizer(grid_sizer_1);
  grid_sizer_1->Fit(this);
  grid_sizer_1->SetSizeHints(this);
  Layout();
}

void Plot3DWiz::SetValue(wxString s) {
  if (s.StartsWith(wxS("plot3d")))
    Parse(s);
  else if (s.StartsWith(wxS("wxplot3d"))) {
    Parse(s.SubString(2, s.Length()));
    combo_box_1->SetValue(_("inline"));
  } else
    text_ctrl_1->SetValue(s);

  text_ctrl_1->SetSelection(-1, -1);
}

void Plot3DWiz::Parse(wxString s) {
  unsigned int i = 0;
  wxString curr;
  s = s.SubString(7, s.Length());
  // Function to plot
  if (s.StartsWith(wxS("["))) {
    int depth = 0;
    do {
      if (s.GetChar(i) == '[') {
        depth++;
        if (depth > 1)
          curr += s.GetChar(i);
      } else if (s.GetChar(i) == ']') {
        depth--;
        if (depth > 0)
          curr += s.GetChar(i);
      } else
        curr += s.GetChar(i);
      i++;
    } while (depth > 0);
  } else {
    while (i < s.Length() && s.GetChar(i) != ',') {
      curr += s.GetChar(i);
      i++;
    }
  }
  text_ctrl_1->SetValue(curr);
  // Independent variable 1
  while (i < s.Length() && s.GetChar(i) != '[')
    i++;
  i++;
  curr = wxEmptyString;
  while (i < s.Length() && s.GetChar(i) != ',') {
    curr += s.GetChar(i);
    i++;
  }
  text_ctrl_2->SetValue(curr);
  i++;
  curr = wxEmptyString;
  while (i < s.Length() && s.GetChar(i) != ',') {
    curr += s.GetChar(i);
    i++;
  }
  text_ctrl_3->SetValue(curr);
  i++;
  curr = wxEmptyString;
  while (i < s.Length() && s.GetChar(i) != ']') {
    curr += s.GetChar(i);
    i++;
  }
  text_ctrl_4->SetValue(curr);
  i++;
  // Independent variable 2
  while (i < s.Length() && s.GetChar(i) != '[')
    i++;
  i++;
  curr = wxEmptyString;
  while (i < s.Length() && s.GetChar(i) != ',') {
    curr += s.GetChar(i);
    i++;
  }
  text_ctrl_5->SetValue(curr);
  i++;
  curr = wxEmptyString;
  while (i < s.Length() && s.GetChar(i) != ',') {
    curr += s.GetChar(i);
    i++;
  }
  text_ctrl_6->SetValue(curr);
  i++;
  curr = wxEmptyString;
  while (i < s.Length() && s.GetChar(i) != ']') {
    curr += s.GetChar(i);
    i++;
  }
  text_ctrl_7->SetValue(curr);
  i++;
  // Optional parameters
  while (i < s.Length()) {
    if (s.GetChar(i) == '[') {
      i++;
      curr = wxEmptyString;
      while (i < s.Length() && s.GetChar(i) != ',') {
        curr += s.GetChar(i);
        i++;
      }
      curr.Trim();
      curr.Trim(false);
      if (curr == wxS("gnuplot_postamble")) {
        while (i < s.Length() && s.GetChar(i) != '"')
          i++;
        i++;
        curr = wxEmptyString;
        while (i < s.Length() && s.GetChar(i) != '"') {
          curr += s.GetChar(i);
          i++;
        }
        combo_box_2->SetValue(curr);
      } else if (curr == wxS("gnuplot_out_file")) {
        while (i < s.Length() && s.GetChar(i) != '"')
          i++;
        i++;
        curr = wxEmptyString;
        while (i < s.Length() && s.GetChar(i) != '"') {
          curr += s.GetChar(i);
          i++;
        }
        text_ctrl_10->SetValue(curr);
      } else if (curr == wxS("gnuplot_pm3d")) {
        curr = wxEmptyString;
        while (i < s.Length() && s.GetChar(i) != ']') {
          curr += s.GetChar(i);
          i++;
        }
        if (curr.Find(wxS("true")) > -1)
          check_box_1->SetValue(true);
        else if (curr.Find(wxS("false")) > -1)
          check_box_1->SetValue(false);
      }
    }
    i++;
  }
}

wxString Plot3DWiz::GetValue() {
  wxString s = wxS("plot3d(");
  wxString p = combo_box_2->GetValue();
  wxString pl = text_ctrl_1->GetValue();
  wxString f = combo_box_1->GetValue();
  wxString file = text_ctrl_10->GetValue();
  int xg = text_ctrl_8->GetValue();
  int yg = text_ctrl_9->GetValue();
  if (pl.Contains(wxS(", ")))
    pl = wxS("[") + pl + wxS("]");
  s += pl;
  s += wxS(", [");
  s += text_ctrl_2->GetValue();
  s += wxS(",") + text_ctrl_3->GetValue();
  s += wxS(",") + text_ctrl_4->GetValue();
  s += wxS("], [");
  s += text_ctrl_5->GetValue();
  s += wxS(",") + text_ctrl_6->GetValue();
  s += wxS(",") + text_ctrl_7->GetValue();
  s += wxS("]");
  if (f != _("default") && f != _("inline"))
    s += wxS(", [plot_format,") + f + wxS("]");
  if (xg != 30 || yg != 30) {
    s += wxS(",\n [grid,");
    s += wxString::Format(wxS("%d"), xg);
    s += wxS(",");
    s += wxString::Format(wxS("%d"), yg);
    s += wxS("]");
  }
#if defined(__WXMSW__)
  if (!check_box_1->IsChecked())
    s += wxS(",\n [gnuplot_pm3d,false]");
#else
  if (check_box_1->IsChecked())
    s += wxS(",\n [gnuplot_pm3d,true]");
#endif

  if (p.Length() > 0)
    s += wxS(",\n [gnuplot_postamble, \"") + p + wxS("\"]");
  if (file.Length()) {
    s += wxS(",\n [gnuplot_term, ps]");
#if defined(__WXMSW__)
    file.Replace(wxS("\\"), wxS("/"));
#endif

    if (file.Right(4) != wxS(".eps") && file.Right(3) != wxS(".ps"))
      file = file + wxS(".eps");
    s += wxS(",\n [gnuplot_out_file, \"") + file + wxS("\"]");
  } else if (f == _("inline"))
    s = wxS("wx") + s;

  s += wxS(")$");

  wxConfig::Get()->Write(wxS("Wiz/Plot3D/format"), combo_box_1->GetSelection());
  wxConfig::Get()->Write(wxS("Wiz/Plot3D/pm3d"), check_box_1->GetValue());
  return s;
}

void Plot3DWiz::OnCombobox(wxCommandEvent &event) {
  wxString selection = combo_box_2->GetStringSelection();
  if (selection.StartsWith(wxS("set mapping cylindrical"))) {
    text_ctrl_2->SetValue(wxS("ph"));
    text_ctrl_3->SetValue(wxS("0"));
    text_ctrl_4->SetValue(wxS("2*%pi"));
    text_ctrl_5->SetValue(wxS("z"));
    text_ctrl_6->SetValue(wxS("0"));
    text_ctrl_7->SetValue(wxS("5"));
    type = cylindrical;
  } else if (selection.StartsWith(wxS("set mapping spherical"))) {
    text_ctrl_2->SetValue(wxS("th"));
    text_ctrl_3->SetValue(wxS("0"));
    text_ctrl_4->SetValue(wxS("2*%pi"));
    text_ctrl_5->SetValue(wxS("ph"));
    text_ctrl_6->SetValue(wxS("-%pi/2"));
    text_ctrl_7->SetValue(wxS("%pi/2"));
    type = spherical;
  } else
    type = cartesian;
  event.Skip();
}

void Plot3DWiz::OnFileBrowse(wxCommandEvent &event) {
  wxString file =
    wxFileSelector(_("Save plot to file"), wxEmptyString, wxS("plot3d.eps"),
		   wxS("eps"), _("Postscript file (*.eps)|*.eps|All|*"),
		   wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
  if (file.Length() > 0)
    text_ctrl_10->SetValue(file);
  event.Skip();
}
