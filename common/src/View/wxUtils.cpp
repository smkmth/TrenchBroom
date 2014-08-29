/*
 Copyright (C) 2010-2014 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#include "wxUtils.h"

#include "IO/Path.h"
#include "IO/ResourceUtils.h"
#include "View/BorderLine.h"
#include "View/MapFrame.h"
#include "View/ViewConstants.h"

#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/window.h>

#include <list>

namespace TrenchBroom {
    namespace View {
        MapFrame* findMapFrame(wxWindow* window) {
            return wxDynamicCast(findFrame(window), MapFrame);
        }

        wxFrame* findFrame(wxWindow* window) {
            if (window == NULL)
                return NULL;
            return wxDynamicCast(wxGetTopLevelParent(window), wxFrame);
        }

        Color fromWxColor(const wxColor& color) {
            const float r = static_cast<float>(color.Red())   / 255.0f;
            const float g = static_cast<float>(color.Green()) / 255.0f;
            const float b = static_cast<float>(color.Blue())  / 255.0f;
            const float a = static_cast<float>(color.Alpha()) / 255.0f;
            return Color(r, g, b, a);
        }
        
        wxColor toWxColor(const Color& color) {
            const unsigned char r = static_cast<unsigned char>(color.r() * 255.0f);
            const unsigned char g = static_cast<unsigned char>(color.g() * 255.0f);
            const unsigned char b = static_cast<unsigned char>(color.b() * 255.0f);
            const unsigned char a = static_cast<unsigned char>(color.a() * 255.0f);
            return wxColor(r, g, b, a);
        }

        wxBitmapButton* createBitmapButton(wxWindow* parent, const String& image, const String& tooltip) {
            wxBitmap bitmap = IO::loadImageResource(IO::Path("images") + IO::Path(image));
            assert(bitmap.IsOk());
            
            wxBitmapButton* button = new wxBitmapButton(parent, wxID_ANY, bitmap, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
            button->SetToolTip(tooltip);
            button->wxWindowBase::SetBackgroundColour(*wxWHITE);
            return button;
        }

        wxSizer* wrapDialogButtonSizer(wxSizer* buttonSizer, wxWindow* parent) {
            wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
            sizer->Add(new BorderLine(parent, BorderLine::Direction_Horizontal), 0, wxEXPAND);
            sizer->AddSpacer(LayoutConstants::DialogButtonTopMargin);
            sizer->Add(buttonSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, LayoutConstants::DialogButtonSideMargin);
            sizer->AddSpacer(LayoutConstants::DialogButtonBottomMargin);
            return sizer;
        }

        wxArrayString filterBySuffix(const wxArrayString& strings, const wxString& suffix, const bool caseSensitive) {
            wxArrayString result;
            for (size_t i = 0; i < strings.size(); ++i) {
                const wxString& str = strings[i];
                if (caseSensitive) {
                    if (str.EndsWith(suffix))
                        result.Add(str);
                } else {
                    if (str.Lower().EndsWith(suffix.Lower()))
                        result.Add(str);
                }
            }
            return result;
        }
    }
}
