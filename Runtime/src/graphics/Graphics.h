#pragma once

// purpose:
// - draw frame
// - handle window dimensions???

namespace rl::impl {
	class Graphics
	{
	public:
		virtual void PrepFrame() = 0;
		virtual void Draw() = 0;
		virtual void Present() = 0;
	};
}