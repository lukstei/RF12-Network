class CreateGroupsSensors< ActiveRecord::Migration
  def self.up
	create_table :groups_sensors, :id => false do |t|
		t.references :sensor
		t.references :group
	end 
  end

  def self.down
	drop_table :groups_sensors
  end
end
