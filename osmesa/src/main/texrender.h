#ifndef TEXRENDER_H
#define TEXRENDER_H


extern void
_mesa_render_texture(GLcontext *ctx,
		     struct gl_framebuffer *fb,
		     struct gl_renderbuffer_attachment *att);

extern void
_mesa_finish_render_texture(GLcontext *ctx,
			    struct gl_renderbuffer_attachment *att);


#endif /* TEXRENDER_H */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
