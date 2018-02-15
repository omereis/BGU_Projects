//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MiscGrid.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
void __fastcall PruneGrid (TStringGrid *grid)
{
	int r, c;

	for (r = grid->FixedRows ; r < grid->RowCount ; r++)
		for (c = grid->FixedCols ; c < grid->ColCount ; c++) {
			grid->Cells[c][r] = "";
			grid->Objects[c][r] = NULL;
		}
}
