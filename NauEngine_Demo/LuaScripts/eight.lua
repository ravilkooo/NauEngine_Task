-- eight.lua
function clamp(x, min, max)
    return math.max(min, math.min(x, max))
end

function update(dt)
    local pos = engine.get_position()
    local x, y, z = pos[1], pos[2], pos[3]
    local t = math.asin(clamp(x * 0.2, -1, 1))
    if (y >= 0 and x >= 0) then
        engine.set_position(5*math.sin(t+dt), 2*math.sin(2*(t+dt)), 0)
        engine.rotate(0, 0, 1, -dt)
    elseif (y <= 0 and x >= 0) then
        t = math.pi - t
        engine.set_position(5*math.sin(t+dt), 2*math.sin(2*(t+dt)), 0)
        engine.rotate(0, 0, 1, -dt)
    elseif (y >= 0 and x <= 0) then
        t = math.pi - t
        engine.set_position(5*math.sin(t+dt), 2*math.sin(2*(t+dt)), 0)
        engine.rotate(0, 0, 1, dt)
    else
        engine.set_position(5*math.sin(t+dt), 2*math.sin(2*(t+dt)), 0)
        engine.rotate(0, 0, 1, dt)
    end
end
