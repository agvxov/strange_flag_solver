package require Tk

wm title . "StrangeFlag Gui"
frame .board
pack .board
for {set i 0} {$i < 5} {incr i} {
    for {set j 0} {$j < 3} {incr j} {
        set color$i$j 0
        canvas .board.c$i$j -width 50 -height 50
        .board.c$i$j create rectangle 0 0 50 50 -fill black
        grid .board.c$i$j -row $i -column $j -sticky news
    }
}
label .messageLabel -text "WIP"
pack .messageLabel
#set message 0

proc updateDisplay {} {
    cUpdateDisplay
    for {set i 0} {$i < 5} {incr i} {
        for {set j 0} {$j < 3} {incr j} {
            .board.c$i$j delete rectangle
            .board.c$i$j create rectangle 0 0 50 50 -fill [set color$i$j]
        }
    }
    if {[info exists ::message]} {
        .messageLabel configure -text $::message
    }
    after 100 updateDisplay
}

after 100 updateDisplay
bind . <Destroy> {exit}
