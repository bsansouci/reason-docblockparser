(** Module [DockBlock]: basic dockblock parsing *)

type parsedValues
(** Shape that describes values that were pulled from dockblocks in file *)

val parseBlock : string list -> parsedValues
(** Get values out of a list of the lines of the document *)