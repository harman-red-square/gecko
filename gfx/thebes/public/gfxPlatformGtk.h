/* -*- Mode: C++; tab-width: 20; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Foundation code.
 *
 * The Initial Developer of the Original Code is Mozilla Foundation.
 * Portions created by the Initial Developer are Copyright (C) 2005
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Vladimir Vukicevic <vladimir@pobox.com>
 *   Masayuki Nakano <masayuki@d-toybox.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef GFX_PLATFORM_GTK_H
#define GFX_PLATFORM_GTK_H

#include "gfxPlatform.h"
#include "nsAutoRef.h"

extern "C" {
    typedef struct _GdkDrawable GdkDrawable;
}

class gfxFontconfigUtils;
#ifndef MOZ_PANGO
class FontFamily;
class FontEntry;
typedef struct FT_LibraryRec_ *FT_Library;
#endif

template <class T>
class gfxGObjectRefTraits : public nsPointerRefTraits<T> {
public:
    static void Release(T *aPtr) { g_object_unref(aPtr); }
    static void AddRef(T *aPtr) { g_object_ref(aPtr); }
};

class THEBES_API gfxPlatformGtk : public gfxPlatform {
public:
    gfxPlatformGtk();
    virtual ~gfxPlatformGtk();

    static gfxPlatformGtk *GetPlatform() {
        return (gfxPlatformGtk*) gfxPlatform::GetPlatform();
    }

    already_AddRefed<gfxASurface> CreateOffscreenSurface(const gfxIntSize& size,
                                                         gfxASurface::gfxImageFormat imageFormat);

    nsresult GetFontList(const nsACString& aLangGroup,
                         const nsACString& aGenericFamily,
                         nsStringArray& aListOfFonts);

    nsresult UpdateFontList();

    nsresult ResolveFontName(const nsAString& aFontName,
                             FontResolverCallback aCallback,
                             void *aClosure, PRBool& aAborted);

    nsresult GetStandardFamilyName(const nsAString& aFontName, nsAString& aFamilyName);

    gfxFontGroup *CreateFontGroup(const nsAString &aFamilies,
                                  const gfxFontStyle *aStyle,
                                  gfxUserFontSet *aUserFontSet);

#ifndef MOZ_PANGO
    FontFamily *FindFontFamily(const nsAString& aName);
    FontEntry *FindFontEntry(const nsAString& aFamilyName, const gfxFontStyle& aFontStyle);
#endif

    static double DPI() {
        if (sDPI < 0.0) {
            InitDPI();
        }
        NS_ASSERTION(sDPI > 0.0, "Something is wrong");
        return sDPI;
    }

#ifndef MOZ_PANGO
    FT_Library GetFTLibrary();
#endif

    void SetGdkDrawable(gfxASurface *target,
                        GdkDrawable *drawable);
    GdkDrawable *GetGdkDrawable(gfxASurface *target);

protected:
    static void InitDPI();

    static double sDPI;
    static gfxFontconfigUtils *sFontconfigUtils;

private:
    virtual cmsHPROFILE GetPlatformCMSOutputProfile();
};

#endif /* GFX_PLATFORM_GTK_H */
