-- rotate.lua
function update(dt)
    local pos = engine.get_position()
    local x, y, z = pos[1], pos[2], pos[3]
    engine.set_position(x, y, z + 10*dt)
end
