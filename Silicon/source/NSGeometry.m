/*	NSGeometry.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/
#include <Silicon/silicon.h>


NSPoint NSMakePoint(CGFloat x, CGFloat y) {
    NSPoint p;
    p.x = x;
    p.y = y;
    return p;
}

NSSize NSMakeSize(CGFloat w, CGFloat h) {
    NSSize s;
    s.width = w;
    s.height = h;
    return s;
}

NSRect NSMakeRect(CGFloat x, CGFloat y, CGFloat w, CGFloat h) {
    NSRect r;
    r.origin.x = x;
    r.origin.y = y;
    r.size.width = w;
    r.size.height = h;
    return r;
}

CGFloat NSMaxX(NSRect aRect) {
    return (aRect.origin.x + aRect.size.width);
}

CGFloat NSMaxY(NSRect aRect) {
    return (aRect.origin.y + aRect.size.height);
}

CGFloat NSMidX(NSRect aRect) {
    return (aRect.origin.x + aRect.size.width * (CGFloat)0.5);
}

CGFloat NSMidY(NSRect aRect) {
    return (aRect.origin.y + aRect.size.height * (CGFloat)0.5);
}

CGFloat NSMinX(NSRect aRect) {
    return (aRect.origin.x);
}

CGFloat NSMinY(NSRect aRect) {
    return (aRect.origin.y);
}

CGFloat NSWidth(NSRect aRect) {
    return (aRect.size.width);
}

CGFloat NSHeight(NSRect aRect) {
    return (aRect.size.height);
}

NSRect NSRectFromCGRect(CGRect cgrect) {
    union _ {NSRect ns; CGRect cg;};
    return ((union _ *)&cgrect)->ns;
}

CGRect NSRectToCGRect(NSRect nsrect) {
    union _ {NSRect ns; CGRect cg;};
    return ((union _ *)&nsrect)->cg;
}

NSPoint NSPointFromCGPoint(CGPoint cgpoint) {
    union _ {NSPoint ns; CGPoint cg;};
    return ((union _ *)&cgpoint)->ns;
}

CGPoint NSPointToCGPoint(NSPoint nspoint) {
    union _ {NSPoint ns; CGPoint cg;};
    return ((union _ *)&nspoint)->cg;
}

NSSize NSSizeFromCGSize(CGSize cgsize) {
    union _ {NSSize ns; CGSize cg;};
    return ((union _ *)&cgsize)->ns;
}

CGSize NSSizeToCGSize(NSSize nssize) {
    union _ {NSSize ns; CGSize cg;};
    return ((union _ *)&nssize)->cg;
}