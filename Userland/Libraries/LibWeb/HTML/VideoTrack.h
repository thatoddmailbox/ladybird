/*
 * Copyright (c) 2023, Tim Flynn <trflynn89@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/String.h>
#include <AK/Time.h>
#include <LibVideo/Containers/Matroska/MatroskaDemuxer.h>
#include <LibVideo/Track.h>
#include <LibWeb/Bindings/PlatformObject.h>

namespace Web::HTML {

class VideoTrack final : public Bindings::PlatformObject {
    WEB_PLATFORM_OBJECT(VideoTrack, Bindings::PlatformObject);

public:
    virtual ~VideoTrack() override;

    void set_video_track_list(Badge<VideoTrackList>, JS::GCPtr<VideoTrackList> video_track_list) { m_video_track_list = video_track_list; }

    Time duration() const { return m_track.video_data().duration; }
    u64 pixel_width() const { return m_track.video_data().pixel_width; }
    u64 pixel_height() const { return m_track.video_data().pixel_height; }

    String const& id() const { return m_id; }
    String const& kind() const { return m_kind; }
    String const& label() const { return m_label; }
    String const& language() const { return m_language; }

    bool selected() const { return m_selected; }
    void set_selected(bool selected);

private:
    explicit VideoTrack(JS::Realm&, JS::NonnullGCPtr<HTMLMediaElement>, NonnullOwnPtr<Video::Matroska::MatroskaDemuxer>, Video::Track);

    virtual JS::ThrowCompletionOr<void> initialize(JS::Realm&) override;
    virtual void visit_edges(Cell::Visitor&) override;

    // https://html.spec.whatwg.org/multipage/media.html#dom-videotrack-id
    String m_id;

    // https://html.spec.whatwg.org/multipage/media.html#dom-videotrack-kind
    String m_kind;

    // https://html.spec.whatwg.org/multipage/media.html#dom-videotrack-label
    String m_label;

    // https://html.spec.whatwg.org/multipage/media.html#dom-videotrack-language
    String m_language;

    // https://html.spec.whatwg.org/multipage/media.html#dom-videotrack-selected
    bool m_selected { false };

    JS::NonnullGCPtr<HTMLMediaElement> m_media_element;
    JS::GCPtr<VideoTrackList> m_video_track_list;

    NonnullOwnPtr<Video::Matroska::MatroskaDemuxer> m_demuxer;
    Video::Track m_track;
};

}
