use Test::More;
use strict;
use warnings;

#plan tests => 43;
# Test of a 100% coverage is off.
plan tests => 19;

BEGIN {
    use FindBin;
    use lib "$FindBin::Bin/../lib";
}

use List::Util qw(first sum);
use Slic3r;
use Slic3r::Geometry qw(X Y scale unscale convex_hull);
use Slic3r::Geometry::Clipper qw(union diff diff_ex offset offset2_ex);
use Slic3r::Surface qw(:types);
use Slic3r::Test;

sub scale_points (@) { map [scale $_->[X], scale $_->[Y]], @_ }

{
    my $expolygon = Slic3r::ExPolygon->new([ scale_points [0,0], [50,0], [50,50], [0,50] ]);
    my $filler = Slic3r::Filler->new_from_type('rectilinear');
    $filler->set_bounding_box($expolygon->bounding_box);
    $filler->set_angle(0);
    my $surface = Slic3r::Surface->new(
        surface_type    => S_TYPE_TOP,
        expolygon       => $expolygon,
    );
    my $flow = Slic3r::Flow->new(
        width           => 0.69,
        height          => 0.4,
        nozzle_diameter => 0.50,
    );
    $filler->set_spacing($flow->spacing);
    foreach my $angle (0, 45) {
        $surface->expolygon->rotate(Slic3r::Geometry::deg2rad($angle), [0,0]);
        print $surface->expolygon->dump_perl();
        my $paths = $filler->fill_surface($surface, density => 0.4);
        #print @$paths;
        #print $paths->wkt(x);
        is_deeply $paths->pp, [[[49969793, 1588882], [302079,1588880], [302079,3099278]]], 'foobar';
        is scalar @$paths, 1, 'one continuous path';
    }
}

__END__
