/*	NSGeometry.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <Silicon/silicon.h>


/* ============ Geometry functions ============ */
/* Creates a new NSRect from the specified values. */
NSPoint NSMakePoint(CGFloat x, CGFloat y) {
	NSPoint p;
	p.x = x;
	p.y = y;
	return p;
}
/* Creates a new NSPoint from the specified values. */
NSSize NSMakeSize(CGFloat w, CGFloat h) {
	NSSize s;
	s.width = w;
	s.height = h;
	return s;
}
/* Returns a new NSSize from the specified values. */
NSRect NSMakeRect(CGFloat x, CGFloat y, CGFloat w, CGFloat h) {
	NSRect r;
	r.origin.x = x;
	r.origin.y = y;
	r.size.width = w;
	r.size.height = h;
	return r;
}
/* Returns the largest x coordinate of a given rectangle. */
CGFloat NSMaxX(NSRect aRect) {
	return (aRect.origin.x + aRect.size.width);
}
/* Returns the largest y coordinate of a given rectangle. */
CGFloat NSMaxY(NSRect aRect) {
	return (aRect.origin.y + aRect.size.height);
}
/* Returns the x coordinate of a given rectangle’s midpoint. */
CGFloat NSMidX(NSRect aRect) {
	return (aRect.origin.x + aRect.size.width * (CGFloat)0.5);
}
/* Returns the y coordinate of a given rectangle’s midpoint. */
CGFloat NSMidY(NSRect aRect) {
	return (aRect.origin.y + aRect.size.height * (CGFloat)0.5);
}
/* Returns the smallest x coordinate of a given rectangle. */
CGFloat NSMinX(NSRect aRect) {
	return (aRect.origin.x);
}
/* Returns the smallest y coordinate of a given rectangle. */
CGFloat NSMinY(NSRect aRect) {
	return (aRect.origin.y);
}
/* Returns the width of the specified rectangle. */
CGFloat NSWidth(NSRect aRect) {
	return (aRect.size.width);
}
/* Returns the height of a given rectangle. */
CGFloat NSHeight(NSRect aRect) {
	return (aRect.size.height);
}
/* Returns an NSRect typecast from a CGRect. */
NSRect NSRectFromCGRect(CGRect cgrect) {
	union _ {NSRect ns; CGRect cg;};
	return ((union _ *)&cgrect)->ns;
}
/* Returns a CGRect typecast from an NSRect. */
CGRect NSRectToCGRect(NSRect nsrect) {
	union _ {NSRect ns; CGRect cg;};
	return ((union _ *)&nsrect)->cg;
}
/* Returns an NSPoint typecast from a CGPoint. */
NSPoint NSPointFromCGPoint(CGPoint cgpoint) {
	union _ {NSPoint ns; CGPoint cg;};
	return ((union _ *)&cgpoint)->ns;
}
/* Returns a CGPoint typecast from an NSPoint. */
CGPoint NSPointToCGPoint(NSPoint nspoint) {
	union _ {NSPoint ns; CGPoint cg;};
	return ((union _ *)&nspoint)->cg;
}
/* Returns an NSSize typecast from a CGSize. */
NSSize NSSizeFromCGSize(CGSize cgsize) {
	union _ {NSSize ns; CGSize cg;};
	return ((union _ *)&cgsize)->ns;
}
/* Returns a CGSize typecast from an NSSize. */
CGSize NSSizeToCGSize(NSSize nssize) {
	union _ {NSSize ns; CGSize cg;};
	return ((union _ *)&nssize)->cg;
}
/* Returns a Boolean value that indicates whether a given point is in a given rectangle. */
bool NSPointInRect(NSPoint aPoint, NSRect aRect) {
	return (aPoint.x >= aRect.origin.x &&  aPoint.x <= aRect.origin.x + aRect.size.width && aPoint.y >= aRect.origin.y && aPoint.y <= aRect.origin.y + aRect.size.height);
}

#ifdef __cplusplus
}
#endif