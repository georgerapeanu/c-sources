program grader;

uses artclass;

{$L graderlib.o}
{$LINKLIB c}
{$LINKLIB jpeg}

type
    graderArrayType = array[0..499, 0..499] of longint;

procedure __grader_init(dim: array of longint; r, g, b: graderArrayType);
    cdecl; external;

var
    dim : array[0..1] of longint;
    r, g, b : graderArrayType;

begin
    __grader_init(dim, r, g, b);
    writeln(style(dim[0], dim[1], r, g, b));
end.
