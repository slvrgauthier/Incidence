--SCRIPT Peaceful_animal

function PeacefulAnimal:action()

	local entities = self:getEntities()
	local size = entities:getSize()
	local angle = 0
	local nb = 0
	for i = 1,size,1 do
		if entities:getType(i)~=PEACEFUL_ANIMAL then
			angle= angle + entities:getAngle(i)
			nb = nb + 1
		end
	end
	if nb ~= 0 then
		angle = angle / nb
		self:setAngle((angle + math.pi)%2*math.pi)
		return "move"
	else
		math.randomseed(os.time())
		math.random()
		math.random()
		local rand = math.floor(math.random()*10000)%5
		if rand == 0 then
			self:setAngle((self:getAngle()-(math.pi/4))%2*math.pi)
		elseif rand == 4 then
			self:setAngle((self:getAngle()+(math.pi/4))%2*math.pi)
		end
		return "move"
	end
end