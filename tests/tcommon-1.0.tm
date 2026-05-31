
namespace eval ::tcommon {
    namespace export begin finish
    namespace ensemble create

    proc begin {} {
        uplevel {
            ::tcltest::configure -verbose {body error start require}
        }
    }

    proc finish {} {
        uplevel {
            set failed_test_count $::tcltest::numTests(Failed)
            ::tcltest::cleanupTests
            # For Ctest
            if {$failed_test_count > 0} {
                exit 1
            } else {
                exit 0
            }
        }
    }
}

package provide tcommon 1.0


# Local Variables:
# mode: tcl
# fill-column: 80
# End:
