// -*- indent-tabs-mode: nil; js-indent-level: 2 -*-
/* vim: set ts=2 et sw=2 tw=80 filetype=javascript: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

/**
 * This handles long arrow key press. When the event is emitted move focus to
 * given direction.
 */

const { utils:Cu } = Components;

Cu.import("resource://gre/modules/XPCOMUtils.jsm");
XPCOMUtils.defineLazyModuleGetter(this, "Navigator",
  "resource://spatialnavigation/Navigator.jsm");

Cu.import("resource://spatialnavigation/InputManager.jsm");

InputManager.on("userinput:long:direction", (aKind, aDirection) => {
  Navigator.moveToward(aDirection);
});
