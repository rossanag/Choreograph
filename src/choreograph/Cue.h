/*
 * Copyright (c) 2014 David Wicks, sansumbrella.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "TimelineItem.h"

namespace choreograph
{

using CueRef = std::shared_ptr<class Cue>;

///
/// Calls a function after time has elapsed.
///
class Cue : public TimelineItem
{
public:
  Cue() = delete;

  /// Control struct for cancelling Cues if needed.
  /// Accessible through the CueOptions struct.
  struct Control
  {
    /// Cancel the cue this belongs to.
    void cancel() { _cancelled = true; }
    /// Returns true iff this control was told to cancel.
    bool cancelled() const { return _cancelled; }
  private:
    bool _cancelled = false;
  };

  /// Creates a cue from a function and a delay.
  Cue( const std::function<void ()> &fn, Time delay );

  /// Returns a weak_ptr to a control that allows you to cancel the Cue.
  std::weak_ptr<Control> getControl() const { return _control; }

  /// Returns true if the cue should still execute.
  bool isInvalid() const override;

  /// Calls cue function if time threshold has been crossed.
  void update() override;

  /// Cues are instantaneous.
  Time getDuration() const override { return 0.0f; }
private:
  std::function<void ()>    _cue;
  std::shared_ptr<Control>  _control;
};

} // namespace choreograph
