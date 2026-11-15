// Channel (SmartCouponDaemon PDB). Declarations only. The bodies are in a later card.
#pragma once

class RefCntObject;

class Channel
{
protected:
    // 0x1F600 (SmartCouponDaemon) TODO(lift-network)
    static void removeSession(RefCntObject* ref1, RefCntObject* ref2, RefCntObject* ref3);

    friend class DelayedRelease;  // ❓ access for DelayedRelease::Add (0x22C70), LTCG folded the callback
};
