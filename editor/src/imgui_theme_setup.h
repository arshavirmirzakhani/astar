#include "imgui/imgui.h"
// designed and modified using Imthemes

void SetupImGuiStyle() {
	// astar style from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha		       = 1.0f;
	style.DisabledAlpha	       = 0.1000000014901161f;
	style.WindowPadding	       = ImVec2(8.0f, 8.0f);
	style.WindowRounding	       = 3.5f;
	style.WindowBorderSize	       = 0.0f;
	style.WindowMinSize	       = ImVec2(30.0f, 30.0f);
	style.WindowTitleAlign	       = ImVec2(0.5f, 0.6000000238418579f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding	       = 4.0f;
	style.ChildBorderSize	       = 1.0f;
	style.PopupRounding	       = 10.0f;
	style.PopupBorderSize	       = 0.0f;
	style.FramePadding	       = ImVec2(5.0f, 3.5f);
	style.FrameRounding	       = 5.0f;
	style.FrameBorderSize	       = 0.0f;
	style.ItemSpacing	       = ImVec2(5.0f, 4.0f);
	style.ItemInnerSpacing	       = ImVec2(5.0f, 5.0f);
	style.CellPadding	       = ImVec2(5.0f, 2.0f);
	style.IndentSpacing	       = 5.0f;
	style.ColumnsMinSpacing	       = 5.0f;
	style.ScrollbarSize	       = 15.0f;
	style.ScrollbarRounding	       = 9.0f;
	style.GrabMinSize	       = 15.0f;
	style.GrabRounding	       = 5.0f;
	style.TabRounding	       = 5.0f;
	style.TabBorderSize	       = 0.0f;
	style.ColorButtonPosition      = ImGuiDir_Right;
	style.ButtonTextAlign	       = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign      = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text]	    = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(1.0f, 1.0f, 1.0f, 0.6351931095123291f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1072961091995239f, 0.100325807929039f, 0.0902576744556427f, 1.0f);
	style.Colors[ImGuiCol_ChildBg]	= ImVec4(1.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_Border] =
	    ImVec4(0.9227467775344849f, 0.5416688323020935f, 0.1108880192041397f, 0.5490196347236633f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1974248886108398f, 0.184594064950943f, 0.1720053851604462f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] =
	    ImVec4(0.8412017226219177f, 0.5887007713317871f, 0.3032658398151398f, 0.5490196347236633f);
	style.Colors[ImGuiCol_FrameBgActive] =
	    ImVec4(0.9227467775344849f, 0.5416688323020935f, 0.1108880192041397f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TitleBg] =
	    ImVec4(0.8412017226219177f, 0.5887007713317871f, 0.3032658398151398f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TitleBgActive] =
	    ImVec4(0.9227467775344849f, 0.5416688323020935f, 0.1108880192041397f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TitleBgCollapsed] =
	    ImVec4(0.8412017226219177f, 0.5887007713317871f, 0.3032658398151398f, 0.5490196347236633f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_ScrollbarBg] =
	    ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 0.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] =
	    ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] =
	    ImVec4(0.2352941185235977f, 0.2352941185235977f, 0.2352941185235977f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] =
	    ImVec4(0.294117659330368f, 0.294117659330368f, 0.294117659330368f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 0.3862661123275757f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] =
	    ImVec4(0.8412017226219177f, 0.5887007713317871f, 0.3032658398151398f, 0.5490196347236633f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 0.3862661123275757f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_Button] =
	    ImVec4(0.8412017226219177f, 0.5887007713317871f, 0.3032658398151398f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ButtonHovered] =
	    ImVec4(0.9227467775344849f, 0.5416688323020935f, 0.1108880192041397f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.0f, 0.3862661123275757f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_Header] =
	    ImVec4(0.8412017226219177f, 0.5887007713317871f, 0.3032658398151398f, 0.5490196347236633f);
	style.Colors[ImGuiCol_HeaderHovered] =
	    ImVec4(0.9227467775344849f, 0.5416688323020935f, 0.1108880192041397f, 0.5490196347236633f);
	style.Colors[ImGuiCol_HeaderActive] =
	    ImVec4(0.9098712205886841f, 0.5066152215003967f, 0.05076535418629646f, 0.5490196347236633f);
	style.Colors[ImGuiCol_Separator] =
	    ImVec4(0.8412017226219177f, 0.5887007713317871f, 0.3032658398151398f, 0.5490196347236633f);
	style.Colors[ImGuiCol_SeparatorHovered] =
	    ImVec4(0.9227467775344849f, 0.5416688323020935f, 0.1108880192041397f, 0.5490196347236633f);
	style.Colors[ImGuiCol_SeparatorActive] =
	    ImVec4(0.9098712205886841f, 0.5066152215003967f, 0.05076535418629646f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ResizeGrip] =
	    ImVec4(0.7686274647712708f, 0.6952285170555115f, 0.5764706134796143f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ResizeGripHovered] =
	    ImVec4(0.8412017226219177f, 0.6881276965141296f, 0.4404575228691101f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ResizeGripActive] =
	    ImVec4(0.8583691120147705f, 0.6655840277671814f, 0.3536628186702728f, 0.5490196347236633f);
	style.Colors[ImGuiCol_Tab] =
	    ImVec4(0.8412017226219177f, 0.5887007713317871f, 0.3032658398151398f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TabHovered] =
	    ImVec4(0.9227467775344849f, 0.5416688323020935f, 0.1108880192041397f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TabActive] =
	    ImVec4(0.9098712205886841f, 0.5066152215003967f, 0.05076535418629646f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0f, 0.4509803950786591f, 1.0f, 0.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] =
	    ImVec4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 0.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.294117659330368f, 0.294117659330368f, 0.294117659330368f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] =
	    ImVec4(0.7372549176216125f, 0.6941176652908325f, 0.886274516582489f, 0.5490196347236633f);
	style.Colors[ImGuiCol_PlotHistogram] =
	    ImVec4(0.7982832789421082f, 0.6404322385787964f, 0.4111330211162567f, 0.5490196347236633f);
	style.Colors[ImGuiCol_PlotHistogramHovered] =
	    ImVec4(0.8412017226219177f, 0.5887007713317871f, 0.3032658398151398f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TableHeaderBg] =
	    ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] =
	    ImVec4(0.9227467775344849f, 0.5416688323020935f, 0.1108880192041397f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TableBorderLight] =
	    ImVec4(0.8412017226219177f, 0.5887007713317871f, 0.3032658398151398f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TableRowBg]    = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.03433477878570557f);
	style.Colors[ImGuiCol_TextSelectedBg] =
	    ImVec4(0.7372549176216125f, 0.6941176652908325f, 0.886274516582489f, 0.5490196347236633f);
	style.Colors[ImGuiCol_DragDropTarget]	     = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
	style.Colors[ImGuiCol_NavHighlight]	     = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] =
	    ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] =
	    ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
}