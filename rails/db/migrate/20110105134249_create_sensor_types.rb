class CreateSensorTypes < ActiveRecord::Migration
  def self.up
    create_table :sensor_types do |t|
		t.string :name, :unit, :interface, :formula
		t.timestamps
    end
  end

  def self.down
    drop_table :sensor_types
  end
end
